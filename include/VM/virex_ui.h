#pragma once
#include <virex.h>

void OnInstructionExecution(Vm *vm, size_t instructionIndex, bool debug);

void OnPause(Vm *vm);