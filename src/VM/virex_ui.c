#include "virex_ui.h"

void OnInstructionExecution(Vm *vm, int instructionIndex, bool debug)
{
    WINDOW *prg = vm->disp.windows[PROGRAM];
    OpcodeDetails details;
    wmove(prg, 1, 1);

    size_t i = (instructionIndex > 0) ? instructionIndex : 0;

    size_t count = (instructionIndex + getmaxy(prg) - 1 > vm->prog.instruction_count) ? vm->prog.instruction_count : instructionIndex + getmaxy(prg) - 1;
    for (; i < count; i++)
    {
        details = getOpcodeDetails(vm->prog.instructions[i].type);
        if (i == instructionIndex)
            wattron(prg, A_REVERSE);

        wprintw(prg, "\n   %ld\t│ %s ", i, details.name);
        if (details.has_operand)
            wprintw(prg, "\t %ld", vm->prog.instructions[i].operand.u64);
        if (details.has_operand2)
            wprintw(prg, "\t %ld", vm->prog.instructions[i].operand2.u64);
        wattroff(prg, A_REVERSE);
    }

    refreshWindow(vm->disp.windows[PROGRAM], getNameForWindow(PROGRAM), 3, 3, 3);
    refreshWindow(vm->disp.windows[OUTPUT], getNameForWindow(OUTPUT), 4, 5, 3);
    refreshWindow(vm->disp.windows[DETAILS], getNameForWindow(DETAILS), 1, 1, 1);
    refreshWindow(vm->disp.windows[MEMORY], getNameForWindow(MEMORY), 2, 2, 3);
    refreshWindow(vm->disp.windows[INPUT], getNameForWindow(INPUT), 5, 5, 3);

    if (debug)
    {
        wgetch(vm->disp.windows[INPUT]);
    }

    wclear(vm->disp.windows[DETAILS]);
    wclear(prg);
    wclear(vm->disp.windows[MEMORY]);

    details = getOpcodeDetails(vm->prog.instructions[instructionIndex].type);
    dumpStack(vm->disp.windows[MEMORY], vm);
    dumpRegs(vm->disp.windows[DETAILS], &(vm->cpu));
    dumpFlags(vm->disp.windows[DETAILS], &(vm->cpu));
    dumpDetails(vm->disp.windows[DETAILS], &details, &vm->prog.instructions[instructionIndex]);
}