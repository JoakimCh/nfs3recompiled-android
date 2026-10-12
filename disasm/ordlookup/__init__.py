from __future__ import absolute_import
import sys
from . import ws2_32
from . import oleaut32

'''
A small module for keeping a database of ordinal to symbol
mappings for DLLs which frequently get linked without symbolic
infoz.
'''

# wsock32.dll numbers three functions otherwise than ws2_32.dll: 10 is
# inet_addr, 11 inet_ntoa and 12 ioctlsocket there (ws2_32: ioctlsocket,
# inet_addr, inet_ntoa).  The rest of Winsock 1.1 -- all NFS III takes from
# it -- is numbered alike.  Taken from ws2_32's table, nfs3.exe's imports came
# out with inet_addr, inet_ntoa and ioctlsocket in each other's places.
wsock32_ord_names = dict(ws2_32.ord_names)
wsock32_ord_names.update({10: b'inet_addr', 11: b'inet_ntoa', 12: b'ioctlsocket'})

ords = {
    b'ws2_32.dll': ws2_32.ord_names,
    b'wsock32.dll': wsock32_ord_names,
    b'oleaut32.dll': oleaut32.ord_names,
}

PY3 = sys.version_info > (3,)

if PY3:
    def formatOrdString(ord_val):
        return 'ord{}'.format(ord_val).encode()
else:
    def formatOrdString(ord_val):
        return b'ord%d' % ord_val


def ordLookup(libname, ord_val, make_name=False):
    '''
    Lookup a name for the given ordinal if it's in our
    database.
    '''
    names = ords.get(libname.lower())
    if names is None:
        if make_name is True:
            return formatOrdString(ord_val)
        return None
    name = names.get(ord_val)
    if name is None:
        return formatOrdString(ord_val)
    return name
