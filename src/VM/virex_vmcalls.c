#include "virex.h"
#include "virex_ui.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
Error vmcall_write(CPU* cpu, Memory* mem, Region* region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count  = cpu->registers.QT.u64;

    if (addr >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    for (uint64_t i = 0; i < count; i += 1) {
        if (mem->memory[addr + i] == '\\') {
            i += 1;
            if (i >= count)
                return ERR_ILLEGAL_OPERAND;
            else if (mem->memory[addr + i] == 'n')
                printOut(OUTPUT, "\n");
            else if (mem->memory[addr + i] == '_')
                printOut(OUTPUT, "_");
            else
                return ERR_ILLEGAL_OPERAND;
        } else if (mem->memory[addr + i] == '_') {
            printOut(OUTPUT, " ");
        } else {
            printOut(OUTPUT, "%c", mem->memory[addr + i]);
        }
    }

    refreshAllWindows();

    return ERR_OK;
}

Error vmcall_alloc(CPU* cpu, Memory* mem, Region* region)
{

    cpu->registers.RF.ptr = allocateRegion(region, cpu->registers.QT.u64);

    return ERR_OK;
}

Error vmcall_free(CPU* cpu, Memory* mem, Region* region)
{
    clearGarbage(region);

    return ERR_OK;
}

Error vmcall_print_f64(CPU* cpu, Memory* mem, Region* region)
{
    printOut(OUTPUT, " %lf\n", cpu->registers.L1.f64);
    return ERR_OK;
}

Error vmcall_print_i64(CPU* cpu, Memory* mem, Region* region)
{
    printOut(OUTPUT, " %" PRId64 "", cpu->registers.L2.i64);
    return ERR_OK;
}

Error vmcall_print_u64(CPU* cpu, Memory* mem, Region* region)
{
    printOut(OUTPUT, " %" PRIu64 "", cpu->registers.L3.u64);
    return ERR_OK;
}

Error vmcall_print_ptr(CPU* cpu, Memory* mem, Region* region)
{
    printOut(OUTPUT, " %p\n", cpu->registers.RF.ptr);
    return ERR_OK;
}

Error vmcall_dump_memory(CPU* cpu, Memory* mem, Region* region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count  = cpu->registers.QT.u64;

    if (addr >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    for (uint64_t i = 0; i < count; ++i) {
        printOut(OUTPUT, " %02X ", mem->memory[addr + i]);
        if (i % 16 == 15) {
            printOut(OUTPUT, "\n ");
        }
        refreshAllWindows();
    }
    printOut(OUTPUT, "\n");
    refreshAllWindows();

    return ERR_OK;
}

Error vmcall_writeROM(CPU* cpu, Memory* mem, Region* region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count  = cpu->registers.QT.u64;

    char* buffer    = cpu->registers.RF.ptr;

    if (addr >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY) {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    memcpy(buffer, &mem->memory[addr], count);

    return ERR_OK;
}
