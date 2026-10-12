"""MMX: each instruction as include/mmx.h's x86::mmx has it, in plain C++ on
the register's 64 bits -- no SSE, so nothing to translate on ARM."""
from . import arguments
from capstone import x86


def cg_emms(instruction, function_bounds, function_names):
    return ['cpu.mmx.init();']


def cg_movd(instruction, function_bounds, function_names, op1, op2):
    if op2.type in (x86.X86_OP_IMM, x86.X86_OP_MEM) or (op2.type == x86.X86_OP_REG and op2.size == 4):
        # Into an MMX register: a dword -- a register's, an immediate,
        # memory's -- the rest 0.
        return ['%s = { x86::mmx::movd(%s) };' % (arguments.get_mmx_value(instruction, op1),
                                                arguments.get_value(instruction, op2))]
    elif op1.type == x86.X86_OP_MEM or (op1.type == x86.X86_OP_REG and op1.size == 4):
        # Out of one: its low dword, into memory or a register.
        return ['%s = x86::mmx::dword(%s, 0);' % (arguments.get_value(instruction, op1),
                                                 arguments.get_mmx_value(instruction, op2))]
    else:
        assert False, instruction.op_str


def cg_movq(instruction, function_bounds, function_names, op1, op2):
    if op1.type == x86.X86_OP_MEM:
        return ['%s = %s;' % (arguments.get_value(instruction, op1),
                              arguments.get_mmx_value(instruction, op2))]
    else:
        return ['%s = %s;' % (arguments.get_mmx_value(instruction, op1),
                              arguments.get_mmx_value(instruction, op2))]


def _operation(name):
    """op1 = x86::mmx::name(op1, op2): op2 a register, memory's 64 bits or, for
    a shift, an immediate."""
    def cg(instruction, function_bounds, function_names, op1, op2):
        source = (arguments.get_value(instruction, op2) if op2.type == x86.X86_OP_IMM
                  else arguments.get_mmx_value(instruction, op2))
        return ['%s = { x86::mmx::%s(%s, %s) };' % (arguments.get_mmx_value(instruction, op1), name,
                                                   arguments.get_mmx_value(instruction, op1), source)]
    return cg


cg_pand = _operation('pand')
cg_por = _operation('por')
cg_pxor = _operation('pxor')
cg_paddw = _operation('paddw')
cg_paddd = _operation('paddd')
cg_paddsb = _operation('paddsb')
cg_paddsw = _operation('paddsw')
cg_pmulhw = _operation('pmulhw')
cg_pmaddwd = _operation('pmaddwd')
cg_psllw = _operation('psllw')
cg_pslld = _operation('pslld')
cg_psllq = _operation('psllq')
cg_psrlw = _operation('psrlw')
cg_psrld = _operation('psrld')
cg_psrlq = _operation('psrlq')
cg_psraw = _operation('psraw')
cg_psrad = _operation('psrad')
cg_punpcklbw = _operation('punpcklbw')
cg_punpckhbw = _operation('punpckhbw')
cg_punpcklwd = _operation('punpcklwd')
cg_punpckhwd = _operation('punpckhwd')
cg_punpckldq = _operation('punpckldq')
cg_punpckhdq = _operation('punpckhdq')
cg_packuswb = _operation('packuswb')
cg_packsswb = _operation('packsswb')
cg_packssdw = _operation('packssdw')
