#include "virex.h"
#include "virex_ui.h"

inline Register *getReg(RegID id, Vm *vm)
{
    return &vm->cpu.registers.reg[id];
}

inline void setReg(RegID id, Vm *vm, DataEntry val)
{
    Register *tmp = getReg(id, vm);
    tmp->u64 = val;
}

inline uint64_t getInstCnt(Vm *vm)
{
    return vm->prog.instruction_count;
}

inline Instruction *getInstructionAt(Vm *vm, uint64_t index)
{
    return &vm->prog.instructions[index];
}

inline QuadWord *getStack(Vm *vm)
{
    return vm->mem.stack;
}

inline Byte *getMemory(Vm *vm)
{
    return vm->mem.memory;
}

void executeProgram(Vm *vm, int debug, int lim)
{
    size_t c = getReg(REG_NX, vm)->u64;
    Error error = executeInst(vm, vm->disp.windows[OUTPUT]);

    if (debug > 0)
    {
        OnInstructionExecution(vm, c, debug == 1);
    }

    if (lim == 0 || getFlag(META_HALT, &(vm->cpu)))
    {
        return;
    }

    if (error != ERR_OK)
        executionErrorWithExit(&error);

    executeProgram(vm, debug, lim - 1);
}

#define READ_OP(type, out)                                                                                             \
    {                                                                                                                  \
        if (getReg(REG_SP, vm)->u64 < 1)                                                                               \
        {                                                                                                              \
            return ERR_STACK_UNDERFLOW;                                                                                \
        }                                                                                                              \
        const MemoryAddr addr = getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;                                         \
        if (addr >= MEMORY_CAPACITY)                                                                                   \
        {                                                                                                              \
            return ERR_ILLEGAL_MEMORY_ACCESS;                                                                          \
        }                                                                                                              \
        type tmp;                                                                                                      \
        memcpy(&tmp, &getMemory(vm)[addr], sizeof(type));                                                              \
        getStack(vm)[getReg(REG_SP, vm)->u64 - 1].out = tmp;                                                           \
        getReg(REG_NX, vm)->u64++;                                                                                     \
    }

#define ARITH_OP(reg, in, op)                                                                                          \
    {                                                                                                                  \
        reg = reg op in;                                                                                               \
        getReg(REG_NX, vm)->u64++;                                                                                     \
    }

#define BINARY_OP(in, out, op)                                                                                         \
    {                                                                                                                  \
        if (getReg(REG_SP, vm)->u64 < 2)                                                                               \
        {                                                                                                              \
            return ERR_STACK_UNDERFLOW;                                                                                \
        }                                                                                                              \
        getStack(vm)[getReg(REG_SP, vm)->u64 - 2].out =                                                                \
            getStack(vm)[getReg(REG_SP, vm)->u64 - 2].in op getStack(vm)[getReg(REG_SP, vm)->u64 - 1].in;              \
        getReg(REG_SP, vm)->u64 -= 1;                                                                                  \
        getReg(REG_NX, vm)->u64++;                                                                                     \
    }

#define CAST_OP(r1, r2, src, dst, cast)                                                                                \
    {                                                                                                                  \
        r1->dst = cast r2->src;                                                                                        \
        getReg(REG_NX, vm)->u64++;                                                                                     \
    }

Error executeInst(Vm *vm, WINDOW *win)
{
    if (getReg(REG_NX, vm)->u64 >= getInstCnt(vm))
    {
        printf("error %ld %ld", getReg(REG_NX, vm)->u64, getInstCnt(vm));
        return ERR_ILLEGAL_INST_ACCESS;
    }
    Instruction inst = *getInstructionAt(vm, getReg(REG_NX, vm)->u64);
    if (inst.opr1IsReg && inst.operand.u64 > REG_COUNT)
    {
        inst.operand.u64 = getReg(inst.operand.u64 % REG_COUNT, vm)->u64;
    }
    if (inst.opr2IsReg && inst.operand2.u64 > REG_COUNT)
    {
        inst.operand2.u64 = getReg(inst.operand2.u64 % REG_COUNT, vm)->u64;
    }

    // printf("\nenter : %d %s", inst.type, OpcodeDetailsLUT[inst.type].name);
    switch (inst.type)
    {

    case INST_DONOP:
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_RETVL:

        break;

    case INST_INVOK:
        if (inst.operand.u64 > vm->vmCalls.internalVmCallsDefined)
            return ERR_ILLEGAL_OPERAND;

        if (!vm->vmCalls.VmCallI[inst.operand.u64])
            return ERR_NULL_CALL;

        const Error err = vm->vmCalls.VmCallI[inst.operand.u64](&vm->cpu, &vm->mem, win, &vm->region);
        if (err != ERR_OK)
            return err;

        getReg(REG_NX, vm)->u64++;
        break;
    case INST_PUSHR:
        if (getReg(REG_SP, vm)->u64 >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;

        getStack(vm)[getReg(REG_SP, vm)->u64++] = *getReg(inst.operand.u64, vm);
        getReg(REG_NX, vm)->u64++;
        break;
    case INST_SPOPR:
        if (getReg(REG_SP, vm)->u64 < 1)
            return ERR_STACK_UNDERFLOW;

        *getReg(inst.operand.u64, vm) = getStack(vm)[getReg(REG_SP, vm)->u64 - 1];
        getReg(REG_SP, vm)->u64 -= 1;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_SHUTS:
        setFlag(META_HALT, &vm->cpu, 1);
        break;

    case INST_SETR:
        vm->cpu.registers.reg[inst.operand2.u64].u64 = inst.operand.u64;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_GETR:
        getStack(vm)[getReg(REG_SP, vm)->u64++] = *getReg(inst.operand.u64, vm);
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_CALL:
        if (getReg(REG_SP, vm)->u64 >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;

        getStack(vm)[getReg(REG_SP, vm)->u64++].u64 = getReg(REG_NX, vm)->u64 + 1;
        setReg(REG_NX, vm, inst.operand.u64);
        break;

    case INST_LOOP:
        if (getReg(inst.operand2.u64, vm)->u64 > 0)
        {
            setReg(REG_NX, vm, inst.operand.u64);
        }
        else
        {
            getReg(REG_NX, vm)->u64++;
        }
        getReg(inst.operand2.u64, vm)->u64 -= 1;
        break;

    case INST_PUSH:
        if (getReg(REG_SP, vm)->u64 >= STACK_CAPACITY)
        {
            return ERR_STACK_OVERFLOW;
        }
        getStack(vm)[getReg(REG_SP, vm)->u64++] = inst.operand;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_SPOP:
        if (getReg(REG_SP, vm)->u64 < 1)
        {
            return ERR_STACK_UNDERFLOW;
        }
        setReg(REG_QT, vm, getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64);
        getReg(REG_SP, vm)->u64 -= 1;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_SWAP:
        if (inst.operand.u64 >= getReg(REG_SP, vm)->u64)
        {
            return ERR_STACK_UNDERFLOW;
        }

        const uint64_t a = getReg(REG_SP, vm)->u64 - 1;
        const uint64_t b = getReg(REG_SP, vm)->u64 - 1 - inst.operand.u64;

        QuadWord t = getStack(vm)[a];
        getStack(vm)[a] = getStack(vm)[b];
        getStack(vm)[b] = t;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_ADDI:
        ARITH_OP(getReg(REG_L2, vm)->i64, inst.operand.i64, +);
        break;

    case INST_SUBI:
        ARITH_OP(getReg(REG_L2, vm)->i64, inst.operand.i64, -);
        break;

    case INST_MULI:
        ARITH_OP(getReg(REG_L2, vm)->i64, inst.operand.i64, *);
        break;

    case INST_DIVI:
        if (inst.operand.i64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(getReg(REG_L2, vm)->i64, inst.operand.i64, /);
        break;

    case INST_MODI:
        if (inst.operand.i64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(getReg(REG_L2, vm)->i64, inst.operand.i64, %);
        break;

    case INST_ADDU:
        ARITH_OP(getReg(REG_L3, vm)->u64, inst.operand.u64, +);
        break;

    case INST_SUBU:
        ARITH_OP(getReg(REG_L3, vm)->u64, inst.operand.u64, -);
        break;

    case INST_MULU:
        ARITH_OP(getReg(REG_L3, vm)->u64, inst.operand.u64, +);
        break;

    case INST_DIVU:
        if (inst.operand.u64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(getReg(REG_L3, vm)->u64, inst.operand.u64, /);
        break;

    case INST_MODU:
        if (inst.operand.u64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(getReg(REG_L3, vm)->u64, inst.operand.u64, %);
        break;

    case INST_ADDF:
        ARITH_OP(getReg(REG_L1, vm)->f64, inst.operand.f64, +);
        break;

    case INST_SUBF:
        ARITH_OP(getReg(REG_L1, vm)->f64, inst.operand.f64, -);
        break;

    case INST_MULF:
        ARITH_OP(getReg(REG_L1, vm)->f64, inst.operand.f64, *);
        break;

    case INST_DIVF:
        if (inst.operand.f64 == 0.0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(getReg(REG_L1, vm)->f64, inst.operand.f64, /);
        break;

    case INST_JMPU:
        setReg(REG_NX, vm, inst.operand.u64);
        break;

    case INST_JMPC:
        if (getReg(REG_SP, vm)->u64 < 1)
            return ERR_STACK_UNDERFLOW;

        if (getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64)
            setReg(REG_NX, vm, inst.operand.u64);
        else
            getReg(REG_NX, vm)->u64++;

        getReg(REG_SP, vm)->u64 -= 1;
        break;

    case INST_ANDB:
        BINARY_OP(u64, u64, &);
        break;

    case INST_NOTB:
        if (getReg(REG_SP, vm)->u64 < 1)
            return ERR_STACK_UNDERFLOW;

        getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64 = ~getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_COPY:
        setReg(inst.operand.u64, vm, getReg(inst.operand2.u64, vm)->u64);
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_DUPS:
        if (getReg(REG_SP, vm)->u64 >= STACK_CAPACITY)
        {
            return ERR_STACK_OVERFLOW;
        }

        if (getReg(REG_SP, vm)->u64 - inst.operand.u64 <= 0)
        {
            return ERR_STACK_UNDERFLOW;
        }

        getStack(vm)[getReg(REG_SP, vm)->u64] = getStack(vm)[getReg(REG_SP, vm)->u64 - 1 - inst.operand.u64];
        getReg(REG_SP, vm)->u64 += 1;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_RET:
        if (getReg(REG_SP, vm)->u64 < 1)
        {
            return ERR_STACK_UNDERFLOW;
        }

        setReg(REG_NX, vm, getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64);
        setReg(REG_SP, vm, getReg(REG_SP, vm)->u64 - 1);
        break;

    case INST_NOT:
        if (getReg(REG_SP, vm)->u64 < 1)
        {
            return ERR_STACK_UNDERFLOW;
        }

        getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64 = !getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;
        getReg(REG_NX, vm)->u64++;
        break;

    case INST_EQI:
        BINARY_OP(i64, u64, ==);
        break;

    case INST_GEI:
        BINARY_OP(i64, u64, >=);
        break;

    case INST_GTI:
        BINARY_OP(i64, u64, >);
        break;

    case INST_LEI:
        BINARY_OP(i64, u64, <=);
        break;

    case INST_LTI:
        BINARY_OP(i64, u64, <);
        break;

    case INST_NEI:
        BINARY_OP(i64, u64, !=);
        break;

    case INST_EQU:
        BINARY_OP(u64, u64, ==);
        break;

    case INST_GEU:
        BINARY_OP(u64, u64, >=);
        break;

    case INST_GTU:
        BINARY_OP(u64, u64, >);
        break;

    case INST_LEU:
        BINARY_OP(u64, u64, <=);
        break;

    case INST_LTU:
        BINARY_OP(u64, u64, <);
        break;

    case INST_NEU:
        BINARY_OP(u64, u64, !=);
        break;

    case INST_EQF:
        BINARY_OP(f64, u64, ==);
        break;

    case INST_GEF:
        BINARY_OP(f64, u64, >=);
        break;

    case INST_GTF:
        BINARY_OP(f64, u64, >);
        break;

    case INST_LEF:
        BINARY_OP(f64, u64, <=);
        break;

    case INST_LTF:
        BINARY_OP(f64, u64, <);
        break;

    case INST_NEF:
        BINARY_OP(f64, u64, !=);
        break;

    case INST_ORB:
        BINARY_OP(u64, u64, |);
        break;

    case INST_XOR:
        BINARY_OP(u64, u64, ^);
        break;

    case INST_SHR:
        BINARY_OP(u64, u64, >>);
        break;

    case INST_SHL:
        BINARY_OP(u64, u64, <<);
        break;

    case INST_I2F:
        CAST_OP(getReg(REG_L1, vm), getReg(REG_L2, vm), i64, f64, (double));
        break;

    case INST_U2F:
        CAST_OP(getReg(REG_L1, vm), getReg(REG_L3, vm), u64, f64, (double));
        break;

    case INST_F2I:
        CAST_OP(getReg(REG_L2, vm), getReg(REG_L1, vm), f64, i64, (int64_t));
        break;

    case INST_F2U:
        CAST_OP(getReg(REG_L3, vm), getReg(REG_L1, vm), f64, u64, (uint64_t)(int64_t));
        break;

    case INST_READ1U:
        READ_OP(uint8_t, u64);
        break;

    case INST_READ2U:
        READ_OP(uint16_t, u64);
        break;

    case INST_READ4U:
        READ_OP(uint32_t, u64);
        break;

    case INST_READ8U:
        READ_OP(uint64_t, u64);
        break;

    case INST_READ1I:
        READ_OP(int8_t, i64);
        break;

    case INST_READ2I:
        READ_OP(int16_t, i64);
        break;

    case INST_READ4I:
        READ_OP(int32_t, i64);
        break;

    case INST_READ8I:
        READ_OP(int64_t, i64);
        break;

    case INST_WRITE1: {
        if (getReg(REG_SP, vm)->u64 < 2)
        {
            return ERR_STACK_UNDERFLOW;
        }
        const MemoryAddr addr = getStack(vm)[getReg(REG_SP, vm)->u64 - 2].u64;
        if (addr >= MEMORY_CAPACITY)
        {
            return ERR_ILLEGAL_MEMORY_ACCESS;
        }
        getMemory(vm)[addr] = (MemoryAddr)getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;
        getReg(REG_SP, vm)->u64 -= 2;
        getReg(REG_NX, vm)->u64++;
    }
    break;

    case INST_WRITE2: {
        if (getReg(REG_SP, vm)->u64 < 2)
        {
            return ERR_STACK_UNDERFLOW;
        }
        const MemoryAddr addr = getStack(vm)[getReg(REG_SP, vm)->u64 - 2].u64;
        if (addr >= MEMORY_CAPACITY - 1)
        {
            return ERR_ILLEGAL_MEMORY_ACCESS;
        }
        Word value = (Word)getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;
        memcpy(&getMemory(vm)[addr], &value, sizeof(value));
        getReg(REG_SP, vm)->u64 -= 2;
        getReg(REG_NX, vm)->u64++;
    }
    break;

    case INST_WRITE4: {
        if (getReg(REG_SP, vm)->u64 < 2)
        {
            return ERR_STACK_UNDERFLOW;
        }
        const MemoryAddr addr = getStack(vm)[getReg(REG_SP, vm)->u64 - 2].u64;
        if (addr >= MEMORY_CAPACITY - 3)
        {
            return ERR_ILLEGAL_MEMORY_ACCESS;
        }
        DoubleWord value = (DoubleWord)getStack(vm)[getReg(REG_SP, vm)->u64 - 1].u64;
        memcpy(&getMemory(vm)[addr], &value, sizeof(value));
        getReg(REG_SP, vm)->u64 -= 2;
        getReg(REG_NX, vm)->u64++;
    }
    break;

    case INST_WRITE8: {
        if (getReg(REG_SP, vm)->u64 < 2)
        {
            return ERR_STACK_UNDERFLOW;
        }
        const MemoryAddr addr = getStack(vm)[getReg(REG_SP, vm)->u64 - 2].u64;
        if (addr >= MEMORY_CAPACITY - 7)
        {
            return ERR_ILLEGAL_MEMORY_ACCESS;
        }
        QuadWord value = getStack(vm)[getReg(REG_SP, vm)->u64 - 1];
        memcpy(&getMemory(vm)[addr], &value, sizeof(value));
        getReg(REG_SP, vm)->u64 -= 2;
        getReg(REG_NX, vm)->u64++;
    }
    break;

    case NUMBER_OF_INSTS:
    default:
        return ERR_ILLEGAL_INST;
    }

    return ERR_OK;
}