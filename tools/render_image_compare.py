#!/usr/bin/env python3
"""Compare renderer RGB images with explicit tolerances and a difference image."""
import argparse
import json
import math
from pathlib import Path
import sys


def read_ppm(path):
    if path.stat().st_size > 64 * 1024 * 1024:
        raise ValueError("Image exceeds 64 MiB")
    data = path.read_bytes()
    at = 0

    def token():
        nonlocal at
        while at < len(data):
            if data[at] in b" \t\r\n":
                at += 1
            elif data[at] == 35:
                end = data.find(b"\n", at)
                if end < 0:
                    raise ValueError("Unterminated PPM comment")
                at = end + 1
            else:
                break
        start = at
        while at < len(data) and data[at] not in b" \t\r\n#":
            at += 1
        if start == at:
            raise ValueError("Truncated PPM header")
        return data[start:at]

    if token() != b"P6":
        raise ValueError("Expected binary RGB PPM (P6)")
    width, height, maximum = int(token()), int(token()), int(token())
    if not 1 <= width <= 4096 or not 1 <= height <= 4096 or maximum != 255:
        raise ValueError("Unsupported PPM dimensions or channel depth")
    # Consume one header delimiter, not arbitrary whitespace in the pixel data.
    if data[at:at + 2] == b"\r\n":
        at += 2
    elif data[at:at + 1] in (b" ", b"\t", b"\r", b"\n"):
        at += 1
    else:
        raise ValueError("Missing PPM header delimiter")
    pixels = data[at:]
    if len(pixels) != width * height * 3:
        raise ValueError("PPM pixel length does not match dimensions")
    return width, height, pixels


def write_ppm(path, width, height, pixels):
    path.write_bytes(f"P6\n{width} {height}\n255\n".encode("ascii") + pixels)


def compare_pixels(reference, candidate, width, height, channel_tolerance=0, max_changed_fraction=0.0):
    if not 0 <= channel_tolerance <= 255 or not math.isfinite(max_changed_fraction) or not 0 <= max_changed_fraction <= 1:
        raise ValueError("Invalid image comparison tolerances")
    count = width * height
    if count <= 0 or len(reference) != count * 3 or len(candidate) != len(reference):
        raise ValueError("Images must have matching positive dimensions and RGB lengths")
    different = over_tolerance = maximum = absolute = squared = 0
    heatmap = bytearray(len(reference))
    if reference != candidate:
        for at in range(0, len(reference), 3):
            delta = [abs(reference[at + channel] - candidate[at + channel]) for channel in range(3)]
            peak = max(delta)
            different += peak != 0
            over_tolerance += peak > channel_tolerance
            maximum = max(maximum, peak)
            absolute += sum(delta)
            squared += sum(value * value for value in delta)
            # Grayscale amplified absolute difference. Full candidate/reference
            # images remain available so the heatmap is not the visual verdict.
            heatmap[at:at + 3] = bytes([min(255, peak * 8)]) * 3
    mse = squared / len(reference)
    fraction = over_tolerance / count
    return {
        "channels": "RGB", "width": width, "height": height,
        "exact": different == 0, "passed": fraction <= max_changed_fraction,
        "channel_tolerance": channel_tolerance, "max_changed_fraction": max_changed_fraction,
        "different_pixels": different, "different_fraction": different / count,
        "over_tolerance_pixels": over_tolerance, "over_tolerance_fraction": fraction,
        "max_channel_error": maximum, "mean_absolute_error": absolute / len(reference),
        "rmse": math.sqrt(mse), "psnr_db": None if mse == 0 else 10 * math.log10(255 * 255 / mse),
        "heatmap_gain": 8,
    }, bytes(heatmap)


def compare_images(reference_path, candidate_path, difference_path, **policy):
    width, height, reference = read_ppm(reference_path)
    other_width, other_height, candidate = read_ppm(candidate_path)
    if (width, height) != (other_width, other_height):
        raise ValueError("Image dimensions differ; images are never resized for comparison")
    report, heatmap = compare_pixels(reference, candidate, width, height, **policy)
    write_ppm(difference_path, width, height, heatmap)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--channel-tolerance", type=int, default=0)
    parser.add_argument("--max-changed-fraction", type=float, default=0)
    args = parser.parse_args()
    try:
        if args.output_dir.exists():
            raise ValueError("Output directory exists; choose a new one")
        args.output_dir.mkdir(parents=True)
        report = compare_images(args.reference, args.candidate, args.output_dir / "difference.ppm",
                                channel_tolerance=args.channel_tolerance, max_changed_fraction=args.max_changed_fraction)
        (args.output_dir / "comparison.json").write_text(json.dumps(report, indent=2) + "\n")
        print(f"{'PASS' if report['passed'] else 'FAIL'}: max channel error {report['max_channel_error']}, "
              f"{report['over_tolerance_fraction']:.4%} pixels beyond tolerance")
        return 0 if report["passed"] else 1
    except (OSError, ValueError) as error:
        print(f"Image comparison failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
