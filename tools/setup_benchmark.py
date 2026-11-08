#!/usr/bin/env python3
"""Download and extract the pinned NFS III final demo data for the benchmark.

No installers are executed. Game data remains in ignored out/benchmark-assets/.
Use --archive for an offline ZIP; it must match the same pinned checksum.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import shutil
import stat
import sys
import tempfile
from urllib.parse import urlsplit
from urllib.request import urlopen
import zipfile


ROOT = Path(__file__).resolve().parents[1]
DEMO_URL = "https://www.nfshome.com/demos.php?download=4"
DEMO_SHA256 = "425e240496a98b2a4543681b35dd92cc340c723b94c13d72755f44de4c90530b"
MAX_DOWNLOAD_BYTES = 32 * 1024 * 1024
MAX_EXTRACTED_BYTES = 64 * 1024 * 1024
SOURCE_DOCS = {"setup/english/readme.txt", "setup/english/license.txt"}


def digest(path):
    checksum = hashlib.sha256()
    with path.open("rb") as source:
        for block in iter(lambda: source.read(1024 * 1024), b""):
            checksum.update(block)
    return checksum.hexdigest()


def check_archive(path):
    if not path.is_file() or path.stat().st_size > MAX_DOWNLOAD_BYTES:
        raise ValueError(f"Missing or oversized demo ZIP: {path}")
    if digest(path) != DEMO_SHA256:
        raise ValueError(f"Demo ZIP checksum mismatch: {path}; expected {DEMO_SHA256}")


def download(url, target):
    if urlsplit(url).scheme != "https":
        raise ValueError("Download URL must use HTTPS")
    target.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary = tempfile.mkstemp(prefix="demo-download-", suffix=".part", dir=target.parent)
    part = Path(temporary)
    try:
        with os.fdopen(descriptor, "wb") as output, urlopen(url, timeout=30) as response:
            if urlsplit(response.geturl()).scheme != "https":
                raise ValueError("Refusing download redirected away from HTTPS")
            length = 0
            while block := response.read(1024 * 1024):
                length += len(block)
                if length > MAX_DOWNLOAD_BYTES:
                    raise ValueError("Demo download exceeds the size limit")
                output.write(block)
        check_archive(part)
        os.replace(part, target)
    finally:
        part.unlink(missing_ok=True)


def selected_entries(archive):
    """Validate archive names and return only data directories and source docs."""
    entries = []
    names = set()
    total = 0
    for entry in archive.infolist():
        name = entry.filename.replace("\\", "/")
        path = PurePosixPath(name)
        if path.is_absolute() or ".." in path.parts or any(":" in part for part in path.parts):
            raise ValueError(f"Unsafe ZIP member: {name}")
        if stat.S_ISLNK(entry.external_attr >> 16):
            raise ValueError(f"ZIP symlinks are unsupported: {name}")
        key = path.as_posix().casefold()
        if not path.parts or not (path.parts[0].casefold() in ("fedata", "gamedata") or key in SOURCE_DOCS):
            continue
        if key in names:
            raise ValueError(f"Duplicate or case-ambiguous ZIP member: {name}")
        names.add(key)
        total += entry.file_size
        if total > MAX_EXTRACTED_BYTES:
            raise ValueError("Demo data exceeds the extraction size limit")
        entries.append((entry, path))
    required = {"gamedata/tracks/trk003/tr03.frd", "gamedata/carmodel/corv/car.viv"}
    if not required.issubset(names):
        raise ValueError("ZIP does not contain the expected final demo data")
    return entries


def extract_or_verify(archive_path, destination):
    check_archive(archive_path)
    with zipfile.ZipFile(archive_path) as archive:
        entries = selected_entries(archive)
        if destination.exists():
            # Compare against the verified ZIP, not a user-editable cached manifest.
            for entry, relative in entries:
                path = destination.joinpath(*relative.parts)
                if any(parent.is_symlink() for parent in (path, *path.parents)):
                    raise ValueError(f"Symlink in demo destination: {path}")
                if entry.is_dir():
                    matches = path.is_dir()
                else:
                    expected = hashlib.sha256(archive.read(entry)).hexdigest()
                    matches = path.is_file() and path.stat().st_size == entry.file_size and digest(path) == expected
                if not matches:
                    raise ValueError(f"Existing demo data differs: {path}; choose another --destination")
            return "Verified existing"
        destination.parent.mkdir(parents=True, exist_ok=True)
        temporary = Path(tempfile.mkdtemp(prefix="demo-extract-", dir=destination.parent))
        try:
            for entry, relative in entries:
                path = temporary.joinpath(*relative.parts)
                if entry.is_dir():
                    path.mkdir(parents=True, exist_ok=True)
                else:
                    path.parent.mkdir(parents=True, exist_ok=True)
                    with archive.open(entry) as source, path.open("xb") as output:
                        shutil.copyfileobj(source, output)
            (temporary / "benchmark-demo.json").write_text(json.dumps({
                "source": DEMO_URL, "archive_sha256": DEMO_SHA256,
                "contents": "FEDATA, GAMEDATA and original readme/license notices; no installer execution",
            }, indent=2) + "\n")
            # Publish the complete extraction only after every member passes CRC.
            temporary.rename(destination)
        finally:
            if temporary.exists():
                shutil.rmtree(temporary)
    return "Prepared"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--archive", type=Path, help="Use an existing ZIP instead of downloading")
    parser.add_argument("--url", default=DEMO_URL, help="HTTPS mirror; the pinned checksum still applies")
    parser.add_argument("--cache-dir", type=Path, default=ROOT / "out/benchmark-assets")
    parser.add_argument("--destination", type=Path, default=ROOT / "out/benchmark-assets/demo")
    args = parser.parse_args()
    try:
        archive = args.archive.resolve() if args.archive else args.cache_dir.resolve() / "nfs3-final-demo.zip"
        if args.archive is None and not archive.exists():
            print("Downloading the pinned NFS III final demo...", flush=True)
            download(args.url, archive)
        result = extract_or_verify(archive, args.destination.resolve())
        print(f"{result} demo data: {args.destination.resolve()}")
        print("Replay: tests/fixtures/renderer-benchmark/joakim.rp3 (included)")
        return 0
    except (OSError, ValueError, zipfile.BadZipFile, RuntimeError) as error:
        print(f"Benchmark setup failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
