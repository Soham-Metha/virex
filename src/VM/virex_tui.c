#include "virex_tui.h"
#include "sasm_instructions.h"

static String WindowNames[MAX_WINDOW_COUNT] = {
    [OUTPUT] = {.data = "OUTPUT", .length = 6},  [DETAILS] = {.data = "DETAILS", .length = 7},
    [MEMORY] = {.data = "MEMORY", .length = 6},  [PROGRAM] = {.data = "PROGRAM", .length = 8},
    [INPUT] = {.data = "INPUT", .length = 6},    [NAME] = {.data = "VIREX", .length = 5},
    [CREDITS] = {.data = "CREDITS", .length = 7}};

String getNameForWindow(int id)
{
    return WindowNames[id];
}
