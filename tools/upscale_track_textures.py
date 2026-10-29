"""A track's textures, unpacked by fsh_textures.py, upscaled 2x by Real-ESRGAN.

  upscale_track_textures.py <realesrgan-ncnn-vulkan.exe> <out> <unpacked>...

Each <unpacked> folder (fsh_textures.py unpack) comes out as <out>/<its
name>, with the same manifest, every picture twice its size; pack it back
with fsh_textures.py pack.

realesrgan-x4plus upscales 4x and the result goes down to 2x by area, which
keeps more of the model's detail than its own 2x does.  Around that:

- Track textures repeat along the road, so every picture goes in wrapped
  round by a quarter of its side and comes out cropped: the model sees the
  seam as the middle of a picture and draws it so.
- The horizon (0000-0007 of the track file) is one panorama in eight
  pieces; it goes in as one strip, wrapped left to right, and is cut back.
- Under transparent pixels the colour is filled in from the opaque ones
  before upscaling, else their black bleeds into the edges.  The alpha goes
  through the model on its own; 1-bit alpha (type 0x7e) is cut at half
  again, 8-bit alpha (the sky's 0x7d) stays as it comes.
- Out of the grain of a 16-bit picture -- its 5-bit steps and dither -- the
  model draws a regular mesh, on the road a different one each piece, which
  shows as a patchwork.  So the road and its concrete (GRAINY) go in with
  that grain taken out (non-local means, DENOISE) and come out with one
  even grain over them all (GRAIN): noise filtered in the frequency domain,
  so that it tiles, the same on every piece.
- Pictures under 16 a side (flat colours mostly) are only resized, and so
  are those of PLAIN, where the mesh would be and taking the grain out
  takes the picture with it: Hometown's brick (0063) and dark roof (0088).
"""

import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

import cv2
import numpy as np

MODEL = "realesrgan-x4plus"
HORIZON = [f"{i:04d}" for i in range(8)]
PLAIN = {"0063", "0088"}
# Hometown's asphalt with and without leaves, the start line and the concrete.
GRAINY = {f"{i:04d}" for i in range(127, 139)} | {"0141"}
DENOISE = 6
GRAIN = 5.0


def read_rgba(path):
    return cv2.cvtColor(cv2.imread(str(path), cv2.IMREAD_UNCHANGED), cv2.COLOR_BGRA2RGBA)


def write_rgba(path, rgba):
    cv2.imwrite(str(path), cv2.cvtColor(rgba, cv2.COLOR_RGBA2BGRA))


def fill_transparent(rgba):
    rgb, alpha = rgba[..., :3].copy(), rgba[..., 3]
    hole = (alpha == 0).astype(np.uint8)
    if hole.all() or not hole.any():
        return rgb
    return cv2.inpaint(rgb, hole, 3, cv2.INPAINT_TELEA)


def grain(height, width, seed):
    """Fine noise of unit deviation that tiles: two scales, low-passed in
    the frequency domain."""
    rng = np.random.default_rng(seed)
    fy, fx = np.fft.fftfreq(height)[:, None], np.fft.fftfreq(width)[None, :]
    total = np.zeros((height, width))
    for sigma, weight in ((0.6, 1.0), (1.6, 0.6)):
        noise = np.real(np.fft.ifft2(np.fft.fft2(rng.standard_normal((height, width)))
                                     * np.exp(-2 * (np.pi * sigma) ** 2 * (fx ** 2 + fy ** 2))))
        total += weight * noise / noise.std()
    return total / total.std()


def padding(height, width):
    return max(4, height // 4), max(4, width // 4)


def run_model(exe, jobs):
    """jobs: name -> RGB uint8 image; the 4x results by the same names."""
    with tempfile.TemporaryDirectory() as temp:
        source, target = Path(temp, "in"), Path(temp, "out")
        source.mkdir()
        target.mkdir()
        for name, rgb in jobs.items():
            cv2.imwrite(str(source / f"{name}.png"), cv2.cvtColor(rgb, cv2.COLOR_RGB2BGR))
        subprocess.run([str(exe), "-i", str(source), "-o", str(target), "-n", MODEL, "-s", "4", "-f", "png"],
                       check=True, cwd=Path(exe).parent, stdout=subprocess.DEVNULL)
        return {name: cv2.cvtColor(cv2.imread(str(target / f"{name}.png")), cv2.COLOR_BGR2RGB) for name in jobs}


def upscale(exe, folder, out):
    manifest = json.loads((folder / "manifest.json").read_text())
    shapes = {s["name"]: s for s in manifest["shapes"]}
    pictures = {name: read_rgba(folder / f"{name}.png") for name in shapes}

    # The pieces that go through the model together, with how they wrap.
    groups = []
    if all(name in pictures for name in HORIZON):
        groups.append((HORIZON, "horizontal"))
    grouped = {n for names, _ in groups for n in names}
    for name, rgba in pictures.items():
        if name not in grouped and name not in PLAIN and min(rgba.shape[:2]) >= 16:
            groups.append(([name], "both"))
            grouped.add(name)

    jobs, layout = {}, {}
    for index, (names, wrap) in enumerate(groups):
        rgba = np.concatenate([pictures[n] for n in names], axis=1)
        h, w = rgba.shape[:2]
        ph, pw = padding(h, pictures[names[0]].shape[1])
        modes = ("wrap", "wrap") if wrap == "both" else ("edge", "wrap")
        def padded(image):
            image = np.pad(image, ((ph, ph), (0, 0), (0, 0)), mode=modes[0])
            return np.pad(image, ((0, 0), (pw, pw), (0, 0)), mode=modes[1])
        colour = padded(fill_transparent(rgba))
        if names[0] in GRAINY:
            colour = cv2.fastNlMeansDenoisingColored(colour, None, DENOISE, DENOISE, 5, 15)
        jobs[f"g{index}"] = colour
        transparent = (rgba[..., 3] < 255).any()
        if transparent:
            jobs[f"g{index}a"] = padded(np.repeat(rgba[..., 3:4], 3, axis=2))
        layout[index] = (names, h, w, ph, pw, transparent)

    results = run_model(exe, jobs)

    done = {}
    for index, (names, h, w, ph, pw, transparent) in layout.items():
        def back(image):
            image = image[ph * 4:(ph + h) * 4, pw * 4:(pw + w) * 4]
            return cv2.resize(image, (w * 2, h * 2), interpolation=cv2.INTER_AREA)
        rgb = back(results[f"g{index}"])
        if transparent:
            alpha = back(results[f"g{index}a"])[..., 0]
        else:
            alpha = np.full(rgb.shape[:2], 255, np.uint8)
        x = 0
        for name in names:
            pw2 = pictures[name].shape[1] * 2
            a = alpha[:, x:x + pw2]
            if shapes[name]["type"] == 0x7E:
                a = np.where(a >= 128, 255, 0).astype(np.uint8)
            done[name] = np.dstack([rgb[:, x:x + pw2], a])
            x += pw2

    for name in GRAINY & done.keys():
        rgba = done[name].astype(np.float32)
        rgba[..., :3] += GRAIN * grain(*rgba.shape[:2], int(name))[..., None]
        done[name] = np.clip(rgba, 0, 255).astype(np.uint8)

    for name, rgba in pictures.items():
        if name not in done:
            h, w = rgba.shape[:2]
            image = cv2.resize(rgba, (w * 2, h * 2), interpolation=cv2.INTER_CUBIC)
            if shapes[name]["type"] == 0x7E:
                image[..., 3] = np.where(image[..., 3] >= 128, 255, 0)
            done[name] = image

    out.mkdir(parents=True, exist_ok=True)
    for name, rgba in done.items():
        write_rgba(out / f"{name}.png", rgba)
    shutil.copy(folder / "manifest.json", out / "manifest.json")


if __name__ == "__main__":
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    exe, out = Path(sys.argv[1]), Path(sys.argv[2])
    for folder in map(Path, sys.argv[3:]):
        upscale(exe, folder, out / folder.name)
        print(folder.name, "done")
