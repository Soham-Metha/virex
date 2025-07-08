#include "virex_ui.h"

volatile display disp;

void initColors()
{
    start_color();
    init_color(COLOR_BLACK, 102, 106, 149);
    init_color(COLOR_RED, 999, 0, 333);
    init_color(COLOR_GREEN, 278, 921, 705);
    init_color(COLOR_YELLOW, 999, 795, 419);
    // init_color(COLOR_BLUE,);
    init_color(COLOR_MAGENTA, 615, 431, 995);
    init_color(COLOR_CYAN, 537, 866, 999);
    init_color(COLOR_WHITE, 815, 815, 815);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
}

void wprintdash(WINDOW *win, int col)
{
    wattron(win, COLOR_PAIR(col));
    int tmp = getmaxx(win) - 1;
    int i, j;
    getyx(win, j, i);
    wmove(win, j, i);
    for (; i < tmp; i++)
    {
        wprintw(win, "─");
    }
    wprintw(win, "\n\n");
    wattroff(win, COLOR_PAIR(col));
}

void dumpStack(WINDOW *win, const Vm *vm)
{
    wprintw(win, "\n\n   ");
    for (uint64_t i = 0; i < 256; i++)
    {
        wprintw(win, "%02X ", vm->mem.memory[i]);
        if (i % 32 == 31)
        {
            wprintw(win, "\n   ");
        }
    }
}

void dumpFlags(WINDOW *win, CPU *cpu)
{
    wprintw(win, "\n");
    wattron(win, A_REVERSE);
    wprintw(win, "  FLAGS ");
    wattroff(win, A_REVERSE);
    wprintdash(win, 1);
    wprintw(win,
            "  HT : %c F1 : %c\t"
            "  F2 : %c F3 : %c\n"
            "  F4 : %c F5 : %c\t"
            "  F6 : %c F7 : %c\n",
            getFlag(META_HALT, cpu) ? 'T' : 'F', getFlag(META_F1, cpu) ? 'T' : 'F', getFlag(META_F2, cpu) ? 'T' : 'F',
            getFlag(META_F3, cpu) ? 'T' : 'F', getFlag(META_F4, cpu) ? 'T' : 'F', getFlag(META_F5, cpu) ? 'T' : 'F',
            getFlag(META_F6, cpu) ? 'T' : 'F', getFlag(META_F7, cpu) ? 'T' : 'F');
}

void dumpRegs(WINDOW *win, CPU *cpu)
{
    wmove(win, 2, 1);
    wattron(win, A_REVERSE);
    wprintw(win, "  REGISTERS ");
    wattroff(win, A_REVERSE);
    wprintdash(win, 1);
    wprintw(win,
            "  H0 : %ld\t"
            "  H1 : %ld\n"
            "  P0 : %ld\t"
            "  P1 : %ld\n"
            "  P2 : %ld\t"
            "  P3 : %ld\n"
            "  JS : %ld\t"
            "  KC : %ld\n"
            "  NX : %ld\t"
            "  SP : %ld\n"
            "  I0 : %ld\n"
            "  I1 : %ld\n"
            "  L0 : %ld\n"
            "  L1 : %lf\n"
            "  L2 : %ld\n"
            "  L3 : %ld\n"
            "  OP : %ld\n"
            "  QT : %ld\n"
            "  RF : %ld\n",
            cpu->registers.H0.u64, cpu->registers.H1.u64, cpu->registers.P0.u64, cpu->registers.P1.u64,
            cpu->registers.P2.u64, cpu->registers.P3.u64, cpu->registers.JS.u64, cpu->registers.KC.u64,
            cpu->registers.NX.u64, cpu->registers.SP.u64, cpu->registers.I0.u64, cpu->registers.I1.u64,
            cpu->registers.L0.u64, cpu->registers.L1.f64, cpu->registers.L2.i64, cpu->registers.L3.u64,
            cpu->registers.OP.u64, cpu->registers.QT.u64, cpu->registers.RF.u64);
}

void dumpDetails(WINDOW *win, OpcodeDetails *details, Instruction *inst)
{
    wprintw(win, "\n");
    wattron(win, A_REVERSE);
    wprintw(win, "  INSTRUCTION ");
    wattroff(win, A_REVERSE);
    wprintdash(win, 1);
    wprintw(win, "  %d\t  %s", details->type, details->name);

    if (details->has_operand)
    {
        wprintw(win,
                "\n────────╮"
                "\n    1.U │ %ld"
                "\n    1.I │ %ld"
                "\n    1.F │ %lf"
                "\n────────╯\n",
                inst->operand.u64, inst->operand.i64, inst->operand.f64);
    }

    if (details->has_operand2)
    {
        wprintw(win,
                "────────╮"
                "\n    2.U │ %ld"
                "\n    2.I │ %ld"
                "\n    2.F │ %lf"
                "\n────────╯\n",
                inst->operand2.u64, inst->operand2.i64, inst->operand2.f64);
    }
}
void updateProgramWindow(Vm *vm, size_t instructionIndex)
{
    WINDOW *prg = disp.windows[PROGRAM];
    wmove(prg, 1, 1);

    size_t i = (instructionIndex > 0) ? instructionIndex : 0;

    size_t count = (instructionIndex + getmaxy(prg) - 1 > (size_t)vm->prog.instruction_count)
                       ? (size_t)vm->prog.instruction_count
                       : instructionIndex + getmaxy(prg) - 1;

    for (; i < count; i++)
    {

        OpcodeDetails details = getOpcodeDetails(vm->prog.instructions[i].type);
        if (i == instructionIndex)
            wattron(prg, A_REVERSE);

        wprintw(prg, "\n   %ld\t│ %s ", i, details.name);
        if (details.has_operand)
            wprintw(prg, "\t %ld", vm->prog.instructions[i].operand.u64);
        if (details.has_operand2)
            wprintw(prg, "\t %ld", vm->prog.instructions[i].operand2.u64);
        wattroff(prg, A_REVERSE);
    }
}

void refreshAllWindows()
{
    refreshWindow(PROGRAM, 3, 3, 3);
    refreshWindow(OUTPUT, 4, 5, 3);
    refreshWindow(DETAILS, 1, 1, 1);
    refreshWindow(MEMORY, 2, 2, 3);
    refreshWindow(INPUT, 5, 5, 3);
}

void clearNonIOWindows()
{
    wclear(disp.windows[PROGRAM]);
    wclear(disp.windows[DETAILS]);
    wclear(disp.windows[MEMORY]);
}

void updateMemoryAndDetailsWindow(Vm *vm, size_t instructionIndex)
{
    OpcodeDetails details = getOpcodeDetails(vm->prog.instructions[instructionIndex].type);
    dumpStack(disp.windows[MEMORY], vm);
    dumpRegs(disp.windows[DETAILS], &(vm->cpu));
    dumpFlags(disp.windows[DETAILS], &(vm->cpu));
    dumpDetails(disp.windows[DETAILS], &details, &vm->prog.instructions[instructionIndex]);
}

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug)
{
    updateProgramWindow(vm, instructionIndex);
    refreshAllWindows(vm);

    if (debug)
    {
        OnPause(vm);
    }

    clearNonIOWindows(vm);
    updateMemoryAndDetailsWindow(vm, instructionIndex);
}

void OnPause(Vm *vm)
{
    wgetch(disp.windows[INPUT]);
}

void OnStart(Vm *vm)
{
    disp = enterTUIMode();
}

int getUserInput(Vm *vm)
{
    int ch;
    int highlight = 0;
    do
    {
        InputMenu(disp.windows[INPUT], &highlight, &ch);
    } while (ch != '\n');

    return highlight;
}

void printOut(int id, const char *str, ...)
{
    va_list args;
    va_start(args, id);
    vwprintw(disp.windows[id], str, args);
    va_end(args);
}

void clearWindow(int id)
{
    wclear(disp.windows[id]);
}

void moveCursorWithinWindow(int id, int y, int x)
{
    wmove(disp.windows[id], y, x);
}

char getChar(int id)
{
    return wgetch(disp.windows[id]);
}

void OnExit()
{
    exitTUIMode(&disp);
}

void refreshWindow(int id, int contentCol, int borderCol, int titleCol)
{
    WINDOW *win = disp.windows[id];
    String str = getNameForWindow(id);
    int x, y;
    getyx(win, y, x);
    if (x < 2)
        x = 2;
    if (y < 2)
        y = 2;

    int tmp = getmaxy(win) - 2;
    while (y > tmp)
    {
        wmove(win, 1, 0);
        wdeleteln(win);
        wmove(win, tmp, 0);
        wdeleteln(win);
        y -= 1;
    }

    wbkgd(win, COLOR_PAIR(contentCol));

    cchar_t vline, hline, ul, ur, ll, lr;

    setcchar(&vline, L"│", 0, 0, NULL);
    setcchar(&hline, L"─", 0, 0, NULL);
    setcchar(&ul, L"╭", 0, 0, NULL);
    setcchar(&ur, L"╮", 0, 0, NULL);
    setcchar(&ll, L"╰", 0, 0, NULL);
    setcchar(&lr, L"╯", 0, 0, NULL);

    wattron(win, COLOR_PAIR(borderCol));
    wborder_set(win, &vline, &vline, &hline, &hline, &ul, &ur, &ll, &lr);
    wattroff(win, COLOR_PAIR(borderCol));

    wattron(win, COLOR_PAIR(titleCol));
    wmove(win, 0, (int)((getmaxx(win) - str.length - 4) / 2));
    // wmove(win, 0, 2);
    wprintw(win, "❮ %s ❯", str.data);
    wattroff(win, COLOR_PAIR(titleCol));

    wmove(win, y, x);
    wrefresh(win);
}

void readFilePath(int id, const char *msg, const char **filePath)
{
    char buffer[100];
    printOut(id, msg);
    wgetnstr(disp.windows[id], buffer, sizeof(buffer) - 1);
    *filePath = strdup(buffer);
}
