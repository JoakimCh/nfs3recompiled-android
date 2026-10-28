"""The loading of the game's data native; never patch input EXEs.

The formats are the ones OpenNFS reads -- RefPack-packed QFS, FSH textures,
FCE models, FRD tracks -- and src/nfs3hp/native_loading.cpp does with them
what the game's own functions do, into the game's own structures, entered from
the top of each generated function the way tools/apply_native_vertices.py
enters the vertex loops: when the native one says no, the generated code runs.

A race's loading, generated: the RefPack decoder copies its output a byte per
emulated step (rep movsb), and the track's FRD is read in a few thousand calls
to a reader and an allocator of a few instructions each.  The FSH textures'
alpha scans this once entered are the port's own since (port_shapes.cpp,
disassemble_nfs3hp.py's PORT_SHAPES_NATIVES), with no generated code behind.
"""
from pathlib import Path

from tools.apply_native_vertices import apply as apply_sites

HEADER = "// Port (tools/apply_native_loading.py): defined in native_loading.cpp.\n"

# (module, function, native stand-in)
SITES = [
    # EA's RefPack decoder, behind every .qfs and packed file.
    ("nfs3hp", "sub_5102a4", "refpack"),
    # An FCE model's polygon records.
    ("nfs3hp", "sub_49cfa0", "fceRecords"),
    # A track's FRD read into its blocks.
    ("nfs3hp", "sub_419c20", "frd"),
]


def apply(root):
    apply_sites(root, SITES, HEADER, "tools/apply_native_loading.py")


if __name__ == "__main__":
    apply(Path(__file__).resolve().parents[1])
