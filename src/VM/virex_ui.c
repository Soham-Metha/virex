#include "virex_ui.h"

typedef struct
{
    WINDOW *windows[MAX_WINDOW_COUNT];
    int windowCount;
} display;

volatile display disp;

static String Inputs[] = {
    [EXEC_SM] = {.data = "Execute the Simulated Machine Code", .length = 34},
    [CUSTOM_CMD] = {.data = "Execute a sasm/orin command with custom flags", .length = 45},
    [ASSEMBLE_EXEC_SASM] = {.data = "Assemble and Execute the Simulated Assembly Code", .length = 48},
    [ASSEMBLE_SASM] = {.data = "Assemble the Simulated Assembly Code into SM", .length = 44},
    [DISASSEMBLE_SM] = {.data = "Disassemble the Simulated Machine Code", .length = 38},
    [COMPILE_ORIN] = {.data = "Compile the ORIN Code into SASM", .length = 33},
    [EXIT_VM] = {.data = "Exit the Virtual Machine", .length = 24}};

static String WindowNames[MAX_WINDOW_COUNT] = {
    [OUTPUT] = {.data = "OUTPUT", .length = 6},  [DETAILS] = {.data = "DETAILS", .length = 7},
    [MEMORY] = {.data = "MEMORY", .length = 6},  [PROGRAM] = {.data = "PROGRAM", .length = 8},
    [INPUT] = {.data = "INPUT", .length = 6},    [NAME] = {.data = "VIREX", .length = 5},
    [CREDITS] = {.data = "CREDITS", .length = 7}};

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
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
}

void refreshWindow(int id, int contentCol, int borderCol, int titleCol)
{
    WINDOW *win = disp.windows[id];
    String str = WindowNames[id];
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
    moveCursorWithinWindow(id, 0, (int)((getmaxx(win) - str.length - 4) / 2));
    // wmove(win, 0, 2);
    printOut(id, "❮ %s ❯", str.data);
    wattroff(win, COLOR_PAIR(titleCol));

    moveCursorWithinWindow(id, y, x);
    wrefresh(win);
}

bool createWindow(int x1, int y1, int x2, int y2, int colorPair)
{
    int width = x2 - x1;
    int height = y2 - y1;

    if (width <= 0 || height <= 0)
    {
        fprintf(stderr, "Error: Invalid window dimensions (%d, %d, %d, %d)\n", x1, y1, x2, y2);
        return false;
    }

    WINDOW *win = newwin(height, width, y1, x1);
    if (!win)
    {
        fprintf(stderr, "Error: Failed to create window\n");
        return false;
    }

    wbkgd(win, COLOR_PAIR(colorPair));
    disp.windows[disp.windowCount++] = win;
    refreshWindow(disp.windowCount - 1, colorPair, 5, 3);

    return true;
}

void CreateWindows()
{
    refresh();
    disp.windowCount = 0;
    int xmin = 0, ymin = 0;
    int xmax = getmaxx(stdscr), ymax = getmaxy(stdscr);

    int xsta = LERP(xmin, xmax, 0.85);
    int xmid = LERP(xsta, xmax, 0.50);
    int xmi2 = LERP(xmin, xmax, 0.68);
    int xen2 = LERP(xmin, xmax, 0.18);
    int ybot = LERP(ymin, ymax, 0.28);
    int ymid = LERP(ymin, ybot, 0.68);

    createWindow(xsta, ymin, xmid, ybot, 1);
    createWindow(xmi2, ybot, xen2, ymax, 5);
    createWindow(xmin, ymin, xsta, ybot, 4);
    createWindow(xmid, ymin, xmax, ymid, 2);
    createWindow(xmid, ymid, xmax, ybot, 3);
    createWindow(xmin, ybot, xmi2, ymax, 7);
    createWindow(xen2, ybot, xmax, ymax, 7);
}

void setInputEnable(bool enable)
{
    
}

void wprintdash(int id, int col)
{
    wattron(disp.windows[id], COLOR_PAIR(col));
    int tmp = getmaxx(disp.windows[id]) - 1;
    int i, j;
    getyx(disp.windows[id], j, i);
    wmove(disp.windows[id], j, i);
    for (; i < tmp; i++)
    {
        wprintw(disp.windows[id], "─");
    }
    wprintw(disp.windows[id], "\n\n");
    wattroff(disp.windows[id], COLOR_PAIR(col));
}

void refreshAllWindows()
{
    refreshWindow(NAME, 7, 7, 3);
    refreshWindow(CREDITS, 7, 7, 3);
    refreshWindow(MEMORY, 2, 2, 3);
    refreshWindow(DETAILS, 1, 1, 3);
    refreshWindow(PROGRAM, 3, 2, 3);
    refreshWindow(OUTPUT, 4, 5, 3);
}

void enterTUIMode()
{
    setlocale(LC_ALL, "");
    initscr();
    clear();
    cbreak();
    // noecho();
    initColors();

    CreateWindows();
    printOut(
        NAME,
        "\n    ██╗   ██╗██╗██████╗ ████████╗██╗   ██╗ █████╗ ██╗     " //      ██╗   ██╗██╗██████╗ ███████╗██╗  ██╗"
        "\n    ██║   ██║██║██╔══██╗╚══██╔══╝██║   ██║██╔══██╗██║     " //      ██║   ██║██║██████╔╝█████╗   ╚███╔╝ "
        "\n    ██║   ██║██║██████╔╝   ██║   ██║   ██║███████║██║     " //      ╚██╗ ██╔╝██║██╔══██╗██╔══╝   ██╔██╗ "
        "\n    ╚██╗ ██╔╝██║██╔══██╗   ██║   ██║   ██║██╔══██║██║     " //       ╚████╔╝ ██║██║  ██║███████╗██╔╝ ██╗"
        "\n     ╚████╔╝ ██║██║  ██║   ██║   ╚██████╔╝██║  ██║███████╗" //        ╚═══╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝"
        "\n      ╚═══╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝"
        "\n    ███████╗██╗  ██╗███████╗ ██████╗██╗   ██╗████████╗ ██████╗ ██████╗ "
        "\n    ██╔════╝╚██╗██╔╝██╔════╝██╔════╝██║   ██║╚══██╔══╝██╔═══██╗██╔══██╗"
        "\n    █████╗   ╚███╔╝ █████╗  ██║     ██║   ██║   ██║   ██║   ██║██████╔╝"
        "\n    ██╔══╝   ██╔██╗ ██╔══╝  ██║     ██║   ██║   ██║   ██║   ██║██╔══██╗"
        "\n    ███████╗██╔╝ ██╗███████╗╚██████╗╚██████╔╝   ██║   ╚██████╔╝██║  ██║"
        "\n    ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═╝"
        "\n                                                                       ");

    printOut(CREDITS, "\n\n    VIREX, SASM\t\t: SOHAM METHA  "
                      "\n    AST visualizer\t: SOHAM METHA  "
                      "\n    Syntax Highlighter\t: SOHAM METHA  "
                      "\n    ORIN Compiler\t: OMKAR JAGTAP "
                      "\n    Core lib(Hashtable)\t: OMKAR JAGTAP  "
                      "\n    Core libs(other)\t: SOHAM METHA  ");

    refreshAllWindows();
    keypad(disp.windows[INPUT], true);
}

void dumpStack(const Memory *mem)
{
    printOut(MEMORY, "\n\n   ");
    for (uint64_t i = 0; i < 256; i++)
    {
        printOut(MEMORY, "%02X ", mem->memory[i]);
        if (i % 32 == 31)
        {
            printOut(MEMORY, "\n   ");
        }
    }
}

void printOutWithColor(int id, int colorPair, const char *str, ...)
{
    va_list args;
    va_start(args, str);
    wattron(disp.windows[id], COLOR_PAIR(colorPair));
    vw_printw(disp.windows[id], str, args);
    wattroff(disp.windows[id], COLOR_PAIR(colorPair));
    va_end(args);
}

void dumpFlags(CPU *cpu)
{
    printOut(DETAILS, "\n");
    printOutWithColor(DETAILS, 8, "  FLAGS ");
    wprintdash(DETAILS, 1);
    printOut(DETAILS,
             "  HT : %c F1 : %c\t"
             "  F2 : %c F3 : %c\n"
             "  F4 : %c F5 : %c\t"
             "  F6 : %c F7 : %c\n",
             getFlag(META_HALT, cpu) ? 'T' : 'F', getFlag(META_F1, cpu) ? 'T' : 'F', getFlag(META_F2, cpu) ? 'T' : 'F',
             getFlag(META_F3, cpu) ? 'T' : 'F', getFlag(META_F4, cpu) ? 'T' : 'F', getFlag(META_F5, cpu) ? 'T' : 'F',
             getFlag(META_F6, cpu) ? 'T' : 'F', getFlag(META_F7, cpu) ? 'T' : 'F');
}

void dumpRegs(CPU *cpu)
{
    moveCursorWithinWindow(DETAILS, 2, 1);
    printOutWithColor(DETAILS, 8, "  REGISTERS ");
    wprintdash(DETAILS, 1);
    printOut(DETAILS,
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

void dumpDetails(Instruction *inst)
{

    OpcodeDetails details = getOpcodeDetails(inst->type);
    printOut(DETAILS, "\n");
    printOutWithColor(DETAILS, 8, "  INSTRUCTION ");
    wprintdash(DETAILS, 1);
    printOut(DETAILS, "  %d\t  %s", details.type, details.name);

    if (details.has_operand)
    {
        printOut(DETAILS,
                 "\n────────╮"
                 "\n    1.U │ %ld"
                 "\n    1.I │ %ld"
                 "\n    1.F │ %lf"
                 "\n────────╯\n",
                 inst->operand.u64, inst->operand.i64, inst->operand.f64);
    }

    if (details.has_operand2)
    {
        printOut(DETAILS,
                 "────────╮"
                 "\n    2.U │ %ld"
                 "\n    2.I │ %ld"
                 "\n    2.F │ %lf"
                 "\n────────╯\n",
                 inst->operand2.u64, inst->operand2.i64, inst->operand2.f64);
    }
}

void updateProgramWindow(size_t instructionIndex, size_t instructionCount, Instruction *inst)
{
    WINDOW *prg = disp.windows[PROGRAM];
    wmove(prg, 1, 1);

    size_t i = (instructionIndex > 0) ? instructionIndex : 0;

    size_t count = (instructionIndex + getmaxy(prg) - 1 > instructionCount) ? instructionCount
                                                                            : instructionIndex + getmaxy(prg) - 1;

    for (; i < count; i++)
    {

        OpcodeDetails details = getOpcodeDetails(inst->type);
        if (i == instructionIndex)
            wattron(prg, A_REVERSE);

        wprintw(prg, "\n   %ld\t│ %s ", i, details.name);
        if (details.has_operand)
            wprintw(prg, "\t %ld", inst->operand.u64);
        if (details.has_operand2)
            wprintw(prg, "\t %ld", inst->operand2.u64);
        wattroff(prg, A_REVERSE);
    }
}

void clearNonIOWindows()
{
    wclear(disp.windows[PROGRAM]);
    wclear(disp.windows[DETAILS]);
    wclear(disp.windows[MEMORY]);
}

void updateMemoryAndDetailsWindow(Vm *vm, size_t instructionIndex)
{
    dumpStack(&vm->mem);
    dumpRegs(&(vm->cpu));
    dumpFlags(&(vm->cpu));
    dumpDetails(&vm->prog.instructions[instructionIndex]);
}

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug)
{
    updateProgramWindow(instructionIndex, vm->prog.instruction_count, &vm->prog.instructions[instructionIndex]);
    refreshAllWindows();

    if (debug)
    {
        OnPause();
    }

    clearNonIOWindows();
    updateMemoryAndDetailsWindow(vm, instructionIndex);
}

void OnPause()
{
    refreshAllWindows();
    wgetch(disp.windows[INPUT]);
}

void OnStart()
{
    enterTUIMode();
}

int getUserInput()
{
    int ch;
    int highlight = 0;
    do
    {
        InputMenu(&highlight, &ch);
    } while (ch != '\n');

    return highlight;
}

void printOut(int id, const char *str, ...)
{
    va_list args;
    va_start(args, str);
    vw_printw(disp.windows[id], str, args);
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
    while (disp.windowCount > 0)
    {
        delwin(disp.windows[disp.windowCount--]);
    }
    endwin();
    exit(0);
}

void readFilePath(int id, const char *msg, const char **filePath)
{
    char buffer[100];
    printOut(id, msg);
    wgetnstr(disp.windows[id], buffer, sizeof(buffer) - 1);
    *filePath = strdup(buffer);
}

void InputMenu(int *highlight, int *ch)
{
    clearWindow(INPUT);
    refreshAllWindows();

    for (int i = 0; i < MAX_INPUTS; i++)
    {
        moveCursorWithinWindow(INPUT, i + 2, 4);

        if (i == *highlight)
        {
            wattron(disp.windows[INPUT], A_REVERSE);
            printOut(INPUT, " ❖  ");
        }
        printOut(INPUT, Inputs[i].data);
        wattroff(disp.windows[INPUT], A_REVERSE);
    }

    *ch = wgetch(disp.windows[INPUT]);

    switch (*ch)
    {
    case KEY_UP:
        *highlight = (*highlight == 0) ? MAX_INPUTS - 1 : *highlight - 1;
        break;
    case KEY_DOWN:
        *highlight = (*highlight + 1) % MAX_INPUTS;
        break;
    default:
        break;
    }
}