#pragma once
#include <virex.h>

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);

void OnStart(Vm *vm);

void OnPause(Vm *vm);

int getUserInput(Vm* vm);