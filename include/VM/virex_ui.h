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

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);

void OnStart();

void OnPause();

void OnExit();

int getUserInput();

void printOut(int id, const char *str, ...);

void clearWindow(int id);

void moveCursorWithinWindow(int id, int y, int x);

char getChar(int id);


void refreshWindow(int id, int contentCol, int borderCol, int titleCol);

void readFilePath(int id, const char *msg, const char **filePath);

void InputMenu(int *highlight, int *ch);
