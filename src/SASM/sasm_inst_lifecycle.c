#include "sasm_assembler.h"

void BeforeLineRead();

void AfterLineRead();

void BeforeFileProcessing(String inputFilePath){
    (void)inputFilePath;
}

void AfterFileProcessing(String inputFilePath, StmtNode *codeBlockBegin) {
    generateASTPng(inputFilePath, codeBlockBegin);
}

void BeforeAssembly();

void AfterAssembly();

void BeforeStatementParse();

void AfterStatementParse();

void BeforeExpressionParse();

void AfterExpressionParse();