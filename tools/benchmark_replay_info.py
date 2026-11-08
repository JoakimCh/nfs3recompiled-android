#!/usr/bin/env python3
"""Inspect a retail/Android RP3 replay and its demo asset dependencies.

This reads metadata only; it does not validate or execute the replay stream.
Offsets follow native_load_saves.cpp and generated sub_478090/sub_478100.
No replay or game files are modified.
"""

import argparse
import hashlib
import json
from pathlib import Path
import struct


SETTINGS_BYTES = 0x20F0
REPLAY_BYTES = 0x296F8
CAR_BASE = 0x19EC
CAR_STRIDE = 0x6C


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def file_identity(path):
    data = path.read_bytes()
    return {"bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def bigf_entries(path):
    data = path.read_bytes()
    if len(data) < 16 or data[:4] != b"BIGF":
        raise ValueError(f"Not a BIGF archive: {path}")
    size, count, header_end = struct.unpack_from(">III", data, 4)
    if size != len(data) or not 16 <= header_end <= size:
        raise ValueError(f"Invalid BIGF header: {path}")
    position = 16
    entries = {}
    for _ in range(count):
        if position + 8 > header_end:
            raise ValueError(f"Truncated BIGF directory: {path}")
        offset, length = struct.unpack_from(">II", data, position)
        position += 8
        end = data.find(b"\0", position, header_end)
        if end < 0 or offset < header_end or offset + length > size:
            raise ValueError(f"Invalid BIGF entry: {path}")
        name = data[position:end].decode("latin-1").casefold()
        entries[name] = data[offset:offset + length]
        position = end + 1
    return entries


def inspect_replay(path):
    data = path.read_bytes()
    if len(data) < REPLAY_BYTES:
        raise ValueError(f"Replay shorter than the fixed image ({REPLAY_BYTES} bytes)")
    if u32(data, 0) != SETTINGS_BYTES or u32(data, 0x1860) != 2:
        raise ValueError("Expected settings size 0x20f0 and replay version 2")
    cars = u32(data, 0x19D0)
    if not 1 <= cars <= (SETTINGS_BYTES - CAR_BASE) // CAR_STRIDE:
        raise ValueError("Car count lies outside the saved settings image")
    player = u32(data, 0x19B4)
    if player >= cars:
        raise ValueError("Player index lies outside the car roster")
    track = u32(data, 0x196C)
    if track > 8:
        raise ValueError("Track is outside the retail replay track range")
    roster = []
    for index in range(cars):
        base = CAR_BASE + index * CAR_STRIDE
        roster.append({
            "slot": index,
            "player": index == player,
            "car_id": data[base:base + 16].hex(),
            # Index is remapped by the engine using car_id when loading.
            "saved_car_index": u32(data, base + 0x14),
        })
    selection_ids = {
        "first_player": data[0x1780:0x1790].hex(),
        "second_player": data[0x17EC:0x17FC].hex(),
    }
    if u32(data, 0x1994) >= 4:
        selection_ids["selected_opponent"] = data[0x1998:0x19A8].hex()
    return {
        "schema": 1,
        "replay": file_identity(path),
        "version": 2,
        "track": track,
        "laps": u32(data, 0x1974),
        "race_kind_raw": u32(data, 0x1878),
        "traffic_setting_raw": u32(data, 0x1990),
        "traffic_disabled": u32(data, 0x1990) == 2,
        "seed": u32(data, 0x20F4),
        "appended_log_flag": u32(data, 0x20F0),
        "bytes_after_fixed_image": len(data) - REPLAY_BYTES,
        "selection_ids": selection_ids,
        "cars": roster,
        "runtime_validated": False,
    }


def inspect_assets(root, report):
    files = {}
    for path in root.rglob("*"):
        if path.is_file():
            key = path.relative_to(root).as_posix().casefold()
            if key in files:
                raise ValueError(f"Case-ambiguous asset: {key}")
            files[key] = path
    models = {}
    for name, path in sorted(files.items()):
        if not name.startswith("gamedata/carmodel/") or not name.endswith("/car.viv"):
            continue
        entries = bigf_entries(path)
        for entry, data in entries.items():
            if entry.startswith("fedata.") and entry != "fedata.fsh" and len(data) >= 0x28:
                if struct.unpack_from("<H", data, 4)[0] != 9:
                    continue
                car_id = data[0x18:0x28].hex()
                model = {"archive": name, **file_identity(path)}
                if "carp.txt" in entries:
                    model["carp_sha256"] = hashlib.sha256(entries["carp.txt"]).hexdigest()
                models.setdefault(car_id, model)
    ids = set(report["selection_ids"].values()) | {car["car_id"] for car in report["cars"]}
    track = report["track"]
    folder = f"gamedata/tracks/trk{track:03d}"
    required = [
        f"{folder}/tr{track:02d}.frd", f"{folder}/tr{track:02d}.col",
        f"{folder}/tr{track:02d}0.qfs", f"{folder}/tr{track:02d}1.qfs",
        f"{folder}/sky.fsh", "gamedata/dashhud/hud98.fsh",
        "gamedata/render/pc/sfx.fsh", "gamedata/render/pc/weather.fsh",
    ]
    missing = [name for name in required if name not in files]
    missing_ids = sorted(ids - models.keys())
    return {
        "matched_models": {key: models[key] for key in sorted(ids & models.keys())},
        "unresolved_car_ids": missing_ids,
        "missing_core_scene_assets": missing,
        "core_scene_assets": {name: file_identity(files[name]) for name in required if name in files},
        "retail_startup_markers_missing": [name for name in (
            "fedata/menus/main.mnu", "gamedata/tracks/trk000/sky.fsh", "install.win"
        ) if name not in files],
        "core_scene_dependencies_found": not missing and not missing_ids,
        "scope": "Core scene assets and saved car IDs only; not all runtime file accesses",
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("replay", type=Path)
    parser.add_argument("--demo-dir", type=Path, help="Extracted root containing fedata and gamedata")
    parser.add_argument("--output", type=Path, help="Optional JSON report; otherwise stdout")
    args = parser.parse_args()
    try:
        report = inspect_replay(args.replay)
        if args.demo_dir:
            if not args.demo_dir.is_dir():
                raise ValueError("Demo directory does not exist")
            report["assets"] = inspect_assets(args.demo_dir, report)
        output = json.dumps(report, indent=2) + "\n"
        if args.output:
            args.output.write_text(output)
        else:
            print(output, end="")
    except (OSError, ValueError, struct.error) as error:
        parser.exit(1, f"Replay inspection failed: {error}\n")


if __name__ == "__main__":
    main()
