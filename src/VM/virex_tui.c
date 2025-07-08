#include "virex_tui.h"
#include "sasm_instructions.h"

static String WindowNames[MAX_WINDOW_COUNT] = {
    [OUTPUT] = {.data = "OUTPUT", .length = 6},  [DETAILS] = {.data = "DETAILS", .length = 7},
    [MEMORY] = {.data = "MEMORY", .length = 6},  [PROGRAM] = {.data = "PROGRAM", .length = 8},
    [INPUT] = {.data = "INPUT", .length = 6},    [NAME] = {.data = "VIREX", .length = 5},
    [CREDITS] = {.data = "CREDITS", .length = 7}};

static String Inputs[] = {
    [EXEC_SM] = {.data = "Execute the Simulated Machine Code", .length = 34},
    [CUSTOM_CMD] = {.data = "Execute a sasm/orin command with custom flags", .length = 45},
    [ASSEMBLE_EXEC_SASM] = {.data = "Assemble and Execute the Simulated Assembly Code", .length = 48},
    [ASSEMBLE_SASM] = {.data = "Assemble the Simulated Assembly Code into SM", .length = 44},
    [DISASSEMBLE_SM] = {.data = "Disassemble the Simulated Machine Code", .length = 38},
    [COMPILE_ORIN] = {.data = "Compile the ORIN Code into SASM", .length = 33},
    [EXIT_VM] = {.data = "Exit the Virtual Machine", .length = 24}};

void InputMenu(WINDOW *win, int *highlight, int *ch)
{
    wclear(win);
    refreshWindow(win, WindowNames[INPUT], 5, 5, 3);

    for (int i = 0; i < MAX_INPUTS; i++)
    {
        wmove(win, i + 2, 4);

        if (i == *highlight)
        {
            wattron(win, A_REVERSE);
            wprintw(win, " ❖  ");
        }
        wprintw(win, "%s", Inputs[i].data);
        wattroff(win, A_REVERSE);
    }

    *ch = wgetch(win);

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
String getNameForWindow(int id)
{
    return WindowNames[id];
}
