"""The specs file's text native; never patch input EXEs.

sub_4b22d0 writes a car's spec record as the text of a specs file -- each of
its 80 entries' name, number and value or values -- into one string on the
game's heap.  src/nfs3hp/native_specs_file.cpp does it natively, entered from
the top of the generated function the way tools/apply_native_vertices.py
enters the vertex loops: when the native one says no (NFS_NATIVES=original),
the generated code runs.  tools/specs_checks holds the native against the
generated code.

Nothing in the game calls it: neither a call nor a pointer to 0x4b22d0 is in
nfs3.exe (checked 2026-10-21), so it is the developers' writer left in.
"""
from pathlib import Path

from tools.apply_native_vertices import apply as apply_sites

HEADER = "// Port (tools/apply_native_specs_file.py): defined in native_specs_file.cpp.\n"

# (module, function, native stand-in)
SITES = [
    ("nfs3hp", "sub_4b22d0", "specsFileLine"),
]


def apply(root):
    apply_sites(root, SITES, HEADER, "tools/apply_native_specs_file.py")


if __name__ == "__main__":
    apply(Path(__file__).resolve().parents[1])
