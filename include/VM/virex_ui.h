#pragma once
#include <virex.h>

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);

void OnStart();

void OnPause();

int getUserInput();

void printOut(int id, const char *str);

void clearWindow(int id);

void moveCursorWithinWindow(int id, int y, int x);

char getChar(int id);