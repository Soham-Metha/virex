#include "virex_tui.h"
#include "sasm_instructions.h"

typedef struct
{
    WINDOW *windows[MAX_WINDOW_COUNT];
    int windowCount;
} display;

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
    keypad(disp.windows[INPUT], enable);
}