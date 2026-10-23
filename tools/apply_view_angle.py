"""View Angle with a third, wider choice; never patch input EXEs.

View Angle in the Graphics menu ([0x6fbc40]) offered two: Wide, 0, which
sub_4dbcc0 makes a horizontal angle of 90 degrees, and Narrow, 1, 75.  The
cameras open from that angle (sub_4dbce0), and tools/apply_widescreen.py widens
it to the screen's shape (Hor+), so on a phone's 20:9 the picture already shows
more than a 4:3 one.  The Modern Patch added a 105 degree choice; this one does
too, as 2: sub_4dbcc0's 90 asks nfs3hp::viewAngleFor, which answers 105 for it.

The menu's list of the choices is the settings record's (0x556758, its list at
+4): text lines ending at a zero, packed against the next setting's, so
nfs3hp::viewAngleStart puts a longer one of its own in guest memory at start --
Normal (the old Wide), Narrow and Wide, the language's own lines 0xaf, 0x113
and 0x112 -- and keeps the values a saved config.dat already holds.
"""
from pathlib import Path

from tools.apply_track_detail import apply as apply_sites

HEADER = "// Port (tools/apply_view_angle.py): defined in nfs3hp_main.cpp.\n"

# (generated file, address and bytes of the instruction, original code, patched
# code, the declaration the patched code needs)
SITES = [
    ("nfs3hp.31.cpp", "004dbcd8  b85a000000",
     "    cpu.eax = 90 /*0x5a*/;",
     "    cpu.eax = viewAngleFor(app, 90 /*0x5a*/); /* port: View Angle's third choice */",
     "x86::reg32 viewAngleFor(win32::WinApplication* app, x86::reg32 angle);\n"),
]


def apply(root):
    apply_sites(root, SITES, HEADER)


if __name__ == "__main__":
    apply(Path(__file__).resolve().parents[1])
