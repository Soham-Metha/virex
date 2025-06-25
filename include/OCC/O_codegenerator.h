/**
 * @file O_codegenerator.h
 * @brief Header file for the code generator module.
 *
 * This file contains the declarations of functions related to code generation from the syntax tree.
 *
 * @author Omkar Jagtap
 * @date January 2025
 */

#pragma once
#include "O_debug_help.h"
#include "O_parse_tree.h"
#include "univ_defs.h"

void intermediateCodeGen(ParseTreeNode*);