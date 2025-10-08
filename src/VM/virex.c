#include "virex.h"
#include "virex_ui.h"

static inline QuadWord stack_pop(Vm* vm)
{
    return vm $stack[--vm $stack_top];
}

static inline void stack_push(Vm* vm, QuadWord val)
{
    vm $stack[vm $stack_top++] = val;
}

void executeProgram(Vm* vm, int debug, int lim)
{
    size_t c    = vm $reg[REG_NX].u64;
    Error error = executeInst(vm);

    if (debug > 0) {
        OnInstructionExecution(vm, c, debug == 1);
    }

    if (lim == 0 || getFlag(META_HALT, &(vm->cpu))) {
        return;
    }

    if (error != ERR_OK)
        executionErrorWithExit(&error);

    executeProgram(vm, debug, lim - 1);
}

#define READ_OP(type, out)                             \
    {                                                  \
        if (vm $stack_top < 1) {                       \
            return ERR_STACK_UNDERFLOW;                \
        }                                              \
        const MemoryAddr addr = stack_pop(vm).u64;     \
        if (addr >= MEMORY_CAPACITY) {                 \
            return ERR_ILLEGAL_MEMORY_ACCESS;          \
        }                                              \
        type tmp;                                      \
        memcpy(&tmp, &vm $memory[addr], sizeof(type)); \
        stack_push(vm, quadwordFrom##out(tmp));        \
        vm $reg[REG_NX].u64++;                         \
    }

#define WRITE_OP(type, size)                              \
    {                                                     \
        if (vm $stack_top < 2) {                          \
            return ERR_STACK_UNDERFLOW;                   \
        }                                                 \
        const type value      = stack_pop(vm).u64;        \
        const MemoryAddr addr = stack_pop(vm).u64;        \
        if (addr >= MEMORY_CAPACITY - size) {             \
            return ERR_ILLEGAL_MEMORY_ACCESS;             \
        }                                                 \
        memcpy(&vm $memory[addr], &value, sizeof(value)); \
        vm $reg[REG_NX].u64++;                            \
    }

#define ARITH_OP(reg, in, op)  \
    {                          \
        reg = reg op in;       \
        vm $reg[REG_NX].u64++; \
    }

#define BINARY_OP(in, out, op)                          \
    {                                                   \
        if (vm $stack_top < 2) {                        \
            return ERR_STACK_UNDERFLOW;                 \
        }                                               \
        in opr2      = stack_pop(vm).in;                \
        in opr1      = stack_pop(vm).in;                \
        QuadWord res = quadwordFrom##out(opr1 op opr2); \
        stack_push(vm, res);                            \
        vm $reg[REG_NX].u64++;                          \
    }

#define CAST_OP(r1, r2, src, dst, cast) \
    {                                   \
        r1.dst = cast r2.src;           \
        vm $reg[REG_NX].u64++;          \
    }

Error executeInst(Vm* vm)
{
    if (vm $reg[REG_NX].u64 >= vm $inst_cnt) {
        printf("error tring to access instruction at '%" PRIu64 "', but there are only '%" PRIu64 "' instructions", vm $reg[REG_NX].u64, vm $inst_cnt);
        return ERR_ILLEGAL_INST_ACCESS;
    }

    Instruction inst = vm $inst[vm $reg[REG_NX].u64];
    if (inst.opr1IsReg && inst.operand.u64 > REG_COUNT) {
        inst.operand.u64 = vm $reg[inst.operand.u64 % REG_COUNT].u64;
    }
    if (inst.opr2IsReg && inst.operand2.u64 > REG_COUNT) {
        inst.operand2.u64 = vm $reg[inst.operand2.u64 % REG_COUNT].u64;
    }

    // printf("\nenter : %d %s", inst.type, OpcodeDetailsLUT[inst.type].name);
    switch (inst.type) {

    case INST_DONOP:
        vm $reg[REG_NX].u64++;
        break;

    case INST_RETVL:
        // no implementation yet!!
        break;

    case INST_SHUTS:
        setFlag(META_HALT, &vm->cpu, 1);
        break;

    case INST_INVOK:
        if (inst.operand.u64 > vm->vmCalls.internalVmCallsDefined)
            return ERR_ILLEGAL_OPERAND;

        if (!vm $vm_call[inst.operand.u64])
            return ERR_NULL_CALL;

        const Error err = vm $vm_call[inst.operand.u64](&vm->cpu, &vm->mem, &vm->region);
        if (err != ERR_OK)
            return err;

        vm $reg[REG_NX].u64++;
        break;

    case INST_GETR: /* fallthrough */
    case INST_PUSHR:
        if (vm $stack_top >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;

        stack_push(vm, vm $reg[inst.operand.u64]);
        vm $reg[REG_NX].u64++;
        break;

    case INST_SPOPR:
        if (vm $stack_top < 1)
            return ERR_STACK_UNDERFLOW;

        vm $reg[inst.operand.u64] = stack_pop(vm);
        vm $reg[REG_NX].u64++;
        break;

    case INST_SETR:
        vm $reg[inst.operand2.u64].u64 = inst.operand.u64;
        vm $reg[REG_NX].u64++;
        break;

    case INST_PUSH:
        if (vm $stack_top >= STACK_CAPACITY) {
            return ERR_STACK_OVERFLOW;
        }
        stack_push(vm, inst.operand);
        vm $reg[REG_NX].u64++;
        break;

    case INST_SPOP:
        if (vm $stack_top < 1) {
            return ERR_STACK_UNDERFLOW;
        }
        vm $reg[REG_QT].u64 = stack_pop(vm).u64;
        vm $reg[REG_NX].u64++;
        break;

    case INST_COPY:
        vm $reg[inst.operand.u64].u64 = vm $reg[inst.operand2.u64].u64;
        vm $reg[REG_NX].u64++;
        break;

    case INST_DUPS:
        if (vm $stack_top >= STACK_CAPACITY) {
            return ERR_STACK_OVERFLOW;
        }

        if (vm $stack_top >= inst.operand.u64) {
            return ERR_STACK_UNDERFLOW;
        }

        stack_push(vm, vm $stack[vm $stack_top - 1 - inst.operand.u64]);
        vm $reg[REG_NX].u64++;
        break;

    case INST_SWAP:
        if (inst.operand.u64 >= vm $stack_top) {
            return ERR_STACK_UNDERFLOW;
        }

        const u64 a  = vm $stack_top - 1;
        const u64 b  = vm $stack_top - 1 - inst.operand.u64;

        QuadWord tmp = vm $stack[a];
        vm $stack[a] = vm $stack[b];
        vm $stack[b] = tmp;
        vm $reg[REG_NX].u64++;
        break;

    case INST_JMPU:
        if (vm $stack_top < 1)
            return ERR_STACK_UNDERFLOW;

        vm $reg[REG_NX].u64 = inst.operand.u64;
        break;

    case INST_JMPC:
        if (vm $stack_top < 1)
            return ERR_STACK_UNDERFLOW;

        if (stack_pop(vm).u64 > 0)
            vm $reg[REG_NX].u64 = inst.operand.u64;
        else
            vm $reg[REG_NX].u64++;

        break;

    case INST_LOOP:
        if (vm $reg[inst.operand2.u64].u64 > 0) {
            vm $reg[REG_NX].u64 = inst.operand.u64;
        } else {
            vm $reg[REG_NX].u64++;
        }
        vm $reg[inst.operand2.u64].u64 -= 1;
        break;

    case INST_CALL:
        if (vm $stack_top >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;

        stack_push(vm, quadwordFromU64(vm $reg[REG_NX].u64 + 1));
        vm $reg[REG_NX].u64 = inst.operand.u64;
        break;

    case INST_RET:
        if (vm $stack_top < 1) {
            return ERR_STACK_UNDERFLOW;
        }

        vm $reg[REG_NX].u64 = stack_pop(vm).u64;
        break;

    case INST_NOT:
        if (vm $stack_top < 1) {
            return ERR_STACK_UNDERFLOW;
        }
        {
            u64 val = stack_pop(vm).u64;
            val     = !val;
            stack_push(vm, quadwordFromU64(val));
        }
        vm $reg[REG_NX].u64++;
        break;

    case INST_NOTB:
        if (vm $stack_top < 1) {
            return ERR_STACK_UNDERFLOW;
        }

        {
            u64 val = stack_pop(vm).u64;
            val     = ~val;
            stack_push(vm, quadwordFromU64(val));
        }
        vm $reg[REG_NX].u64++;
        break;

    case INST_ADDI:
        ARITH_OP(vm $reg[REG_L2].i64, inst.operand.i64, +);
        break;

    case INST_SUBI:
        ARITH_OP(vm $reg[REG_L2].i64, inst.operand.i64, -);
        break;

    case INST_MULI:
        ARITH_OP(vm $reg[REG_L2].i64, inst.operand.i64, *);
        break;

    case INST_DIVI:
        if (inst.operand.i64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(vm $reg[REG_L2].i64, inst.operand.i64, /);
        break;

    case INST_MODI:
        if (inst.operand.i64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(vm $reg[REG_L2].i64, inst.operand.i64, %);
        break;

    case INST_ADDU:
        ARITH_OP(vm $reg[REG_L3].u64, inst.operand.u64, +);
        break;

    case INST_SUBU:
        ARITH_OP(vm $reg[REG_L3].u64, inst.operand.u64, -);
        break;

    case INST_MULU:
        ARITH_OP(vm $reg[REG_L3].u64, inst.operand.u64, +);
        break;

    case INST_DIVU:
        if (inst.operand.u64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(vm $reg[REG_L3].u64, inst.operand.u64, /);
        break;

    case INST_MODU:
        if (inst.operand.u64 == 0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(vm $reg[REG_L3].u64, inst.operand.u64, %);
        break;

    case INST_ADDF:
        ARITH_OP(vm $reg[REG_L1].f64, inst.operand.f64, +);
        break;

    case INST_SUBF:
        ARITH_OP(vm $reg[REG_L1].f64, inst.operand.f64, -);
        break;

    case INST_MULF:
        ARITH_OP(vm $reg[REG_L1].f64, inst.operand.f64, *);
        break;

    case INST_DIVF:
        if (inst.operand.f64 == 0.0)
            return ERR_DIV_BY_ZERO;
        ARITH_OP(vm $reg[REG_L1].f64, inst.operand.f64, /);
        break;

    case INST_ANDB:
        BINARY_OP(u64, U64, &);
        break;

    case INST_EQI:
        BINARY_OP(i64, U64, ==);
        break;

    case INST_GEI:
        BINARY_OP(i64, U64, >=);
        break;

    case INST_GTI:
        BINARY_OP(i64, U64, >);
        break;

    case INST_LEI:
        BINARY_OP(i64, U64, <=);
        break;

    case INST_LTI:
        BINARY_OP(i64, U64, <);
        break;

    case INST_NEI:
        BINARY_OP(i64, U64, !=);
        break;

    case INST_EQU:
        BINARY_OP(u64, U64, ==);
        break;

    case INST_GEU:
        BINARY_OP(u64, U64, >=);
        break;

    case INST_GTU:
        BINARY_OP(u64, U64, >);
        break;

    case INST_LEU:
        BINARY_OP(u64, U64, <=);
        break;

    case INST_LTU:
        BINARY_OP(u64, U64, <);
        break;

    case INST_NEU:
        BINARY_OP(u64, U64, !=);
        break;

    case INST_EQF:
        BINARY_OP(f64, U64, ==);
        break;

    case INST_GEF:
        BINARY_OP(f64, U64, >=);
        break;

    case INST_GTF:
        BINARY_OP(f64, U64, >);
        break;

    case INST_LEF:
        BINARY_OP(f64, U64, <=);
        break;

    case INST_LTF:
        BINARY_OP(f64, U64, <);
        break;

    case INST_NEF:
        BINARY_OP(f64, U64, !=);
        break;

    case INST_ORB:
        BINARY_OP(u64, U64, |);
        break;

    case INST_XOR:
        BINARY_OP(u64, U64, ^);
        break;

    case INST_SHR:
        BINARY_OP(u64, U64, >>);
        break;

    case INST_SHL:
        BINARY_OP(u64, U64, <<);
        break;

    case INST_I2F:
        CAST_OP(vm $reg[REG_L1], vm $reg[REG_L2], i64, f64, (f64));
        break;

    case INST_U2F:
        CAST_OP(vm $reg[REG_L1], vm $reg[REG_L3], u64, f64, (f64));
        break;

    case INST_F2I:
        CAST_OP(vm $reg[REG_L2], vm $reg[REG_L1], f64, i64, (i64));
        break;

    case INST_F2U:
        CAST_OP(vm $reg[REG_L3], vm $reg[REG_L1], f64, u64, (u64)(i64));
        break;

    case INST_READ1U:
        READ_OP(Byte, U64);
        break;

    case INST_READ2U:
        READ_OP(Word, U64);
        break;

    case INST_READ4U:
        READ_OP(DoubleWord, U64);
        break;

    case INST_READ8U:
        READ_OP(u64, U64);
        break;

    case INST_READ1I:
        READ_OP(int8_t, I64);
        break;

    case INST_READ2I:
        READ_OP(int16_t, I64);
        break;

    case INST_READ4I:
        READ_OP(int32_t, I64);
        break;

    case INST_READ8I:
        READ_OP(int64_t, I64);
        break;

    case INST_WRITE1:
        WRITE_OP(Byte, 0);
        break;

    case INST_WRITE2:
        WRITE_OP(Word, 1);
        break;

    case INST_WRITE4:
        WRITE_OP(DoubleWord, 3);
        break;

    case INST_WRITE8:
        WRITE_OP(u64, 7);
        break;

    case NUMBER_OF_INSTS:
    default:
        return ERR_ILLEGAL_INST;
    }

    return ERR_OK;
}