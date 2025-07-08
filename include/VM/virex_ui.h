#pragma once
#include <virex.h>

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);

void OnStart(Vm *vm);

void OnPause(Vm *vm);

int getUserInput(Vm *vm);

void printOut(Vm *vm, int id, const char *str);

void clearWindow(Vm *vm, int id);

void moveCursorWithinWindow(Vm *vm, int id, int y, int x);