#include "virex.h"
#include "virex_ui.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
Error vmcall_write(CPU *cpu, Memory *mem, Region *region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count = cpu->registers.QT.u64;

    if (addr >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    printOut(OUTPUT, "%.*s", (int)count, &mem->memory[addr]);

    refreshWindow(OUTPUT, 1, 5, 3);

    return ERR_OK;
}

Error vmcall_alloc(CPU *cpu, Memory *mem, Region *region)
{

    cpu->registers.RF.ptr = allocateRegion(region, cpu->registers.QT.u64);

    return ERR_OK;
}

Error vmcall_free(CPU *cpu, Memory *mem, Region *region)
{
    clearGarbage(region);

    return ERR_OK;
}

Error vmcall_print_f64(CPU *cpu, Memory *mem, Region *region)
{
    printOut(OUTPUT, " %lf\n", cpu->registers.L1.f64);
    return ERR_OK;
}

Error vmcall_print_i64(CPU *cpu, Memory *mem, Region *region)
{
    printOut(OUTPUT, " %" PRId64 "\n", cpu->registers.L2.i64);
    return ERR_OK;
}

Error vmcall_print_u64(CPU *cpu, Memory *mem, Region *region)
{
    printOut(OUTPUT, " %" PRIu64 "\n", cpu->registers.L3.u64);
    return ERR_OK;
}

Error vmcall_print_ptr(CPU *cpu, Memory *mem, Region *region)
{
    printOut(OUTPUT, " %p\n", cpu->registers.RF.ptr);
    return ERR_OK;
}

Error vmcall_dump_memory(CPU *cpu, Memory *mem, Region *region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count = cpu->registers.QT.u64;

    if (addr >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    for (uint64_t i = 0; i < count; ++i)
    {
        printOut(OUTPUT, " %02X ", mem->memory[addr + i]);
        if (i % 16 == 15)
        {
            printOut(OUTPUT, "\n ");
        }
        refreshWindow(OUTPUT, 1, 5, 3);
    }
    printOut(OUTPUT, "\n");
    refreshWindow(OUTPUT, 1, 5, 3);

    return ERR_OK;
}

Error vmcall_writeROM(CPU *cpu, Memory *mem, Region *region)
{
    MemoryAddr addr = cpu->registers.L0.u64;
    uint64_t count = cpu->registers.QT.u64;

    char *buffer = cpu->registers.RF.ptr;

    if (addr >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    if (addr + count < addr || addr + count >= MEMORY_CAPACITY)
    {
        return ERR_ILLEGAL_MEMORY_ACCESS;
    }

    memcpy(buffer, &mem->memory[addr], count);

    return ERR_OK;
}