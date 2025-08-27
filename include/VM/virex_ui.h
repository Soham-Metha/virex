#pragma once
#include <virex.h>
#define LERP(START, END, T) (START * T + END * (1 - T))

enum WindowID
{
    OUTPUT,
    INPUT,
    DETAILS,
    MEMORY,
    PROGRAM,
    NAME,
    CREDITS,
    MAX_WINDOW_COUNT
};

enum Inputs
{
    EXEC_SM,
    ASSEMBLE_EXEC_SASM,
    CUSTOM_CMD,
    ASSEMBLE_SASM,
    DISASSEMBLE_SM,
    COMPILE_ORIN,
    EXIT_VM,
    MAX_INPUTS
};

// UI Interface abstraction for modularity and future GUI support
/**
 * UI_Interface: Abstract interface for all UI implementations (CLI, TUI, GUI, etc).
 *
 * To add a new UI (such as a GUI), simply implement all functions in this struct for your UI,
 * and set the global UI pointer to your implementation (e.g., UI = &GUI_UI;).
 * This enables seamless switching between CLI, TUI, and future GUI modes.
 */
typedef struct UI_Interface {
    void (*OnInstructionExecution)(Vm *vm, size_t instructionIndex, bool debug);
    void (*OnStart)();
    void (*OnPause)();
    void (*OnExit)();
    int  (*getUserInput)();
    void (*printOut)(int id, const char *str, ...);
    void (*printOutWithColor)(int id, int colorPair, const char *str, ...);
    void (*clearWindow)(int id);
    void (*moveCursorWithinWindow)(int id, int y, int x);
    char (*getChar)(int id);
    void (*refreshAllWindows)();
    void (*readFilePath)(int id, const char *msg, const char **filePath);
    void (*InputMenu)(int *highlight, int *ch);
    void (*SetInputEnable)(bool enable);
};

// Externally accessible UI interface pointer
extern struct UI_Interface *UI;

// Default CLI/TUI implementations (to be defined in respective source files)
void CLI_OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);
void CLI_OnStart();
void CLI_OnPause();
void CLI_OnExit();
int  CLI_getUserInput();
void CLI_printOut(int id, const char *str, ...);
void CLI_printOutWithColor(int id, int colorPair, const char *str, ...);
void CLI_clearWindow(int id);
void CLI_moveCursorWithinWindow(int id, int y, int x);
char CLI_getChar(int id);
void CLI_refreshAllWindows();
void CLI_readFilePath(int id, const char *msg, const char **filePath);
void CLI_InputMenu(int *highlight, int *ch);
void CLI_SetInputEnable(bool enable);

// Add similar declarations for TUI/GUI as needed