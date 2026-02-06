#include "sasm_assembler.h"
#include "univ_fileops.h"
#include "univ_malloc.h"
#include "univ_strings.h"

#pragma GCC diagnostic ignored "-Wunused-result"
const char* inputFile = NULL;
const char* outputFile = NULL;
bool disassemblyMode = false;

void processFlag(Sasm* sasm, const char* program, const char* flag, int* argc, char*** argv);

int main(int argc, char** argv)
{
    freopen("logs.txt", "a", stderr);
    static Sasm sasm = { 0 };
    const char* program = getNextCmdLineArg(&argc, &argv);

    while (argc > 0) {
        const char* flag = getNextCmdLineArg(&argc, &argv);
        processFlag(&sasm, program, flag, &argc, &argv);
    }

    if (!inputFile || !outputFile) {
        displayMsgWithExit("Missing Files\n"
                           "Usage : sasm -i <input file> -o <output file> [-a | -d]\n "
                           "\t default : Assemble mode\n "
                           "\t -d : Disassemble mode\n "
                           "\tAssembly Sample Command    : ./sasm -i ./test.sasm -o ./test.sm \n"
                           "\tDisassembly Sample Command : ./sasm -i ./test.sm -o ./test.sasm -d\n");
    }

    if (!disassemblyMode) {
        translateSasmRootFile(&sasm, convertCstrToStr(inputFile));
        generateSmExecutable(&sasm, outputFile);
        return 0;
    }
    FILE* f = openFile(outputFile, "wb");

    loadSmExecutableIntoSasm(&sasm, inputFile);
    for (InstAddr i = 0; i < sasm.prog.instruction_count; ++i) {
        OpcodeDetails details = getOpcodeDetails(sasm.prog.instructions[i].type);
        if (details.type!=INST_RET) {
            fprintf(f, "\t");
        }
        fprintf(f, "%s\t", details.name);
        if (details.has_operand) {
            fprintf(f, "\t%"    PRIu64, sasm.prog.instructions[i].operand.u64);
        }
        if (details.has_operand2) {
            fprintf(f, "\t%"    PRIu64, sasm.prog.instructions[i].operand2.u64);
        }
        if(sasm.prog.instructions[i].operand.i64!=0)
        fprintf(f, "\t;; 1 i64 %" PRIi64, sasm.prog.instructions[i].operand.i64);
        if(sasm.prog.instructions[i].operand.f64!=0)
        fprintf(f, "\t;; 1 f64 %lf"     , sasm.prog.instructions[i].operand.f64);
    
        if(sasm.prog.instructions[i].operand2.i64!=0)
        fprintf(f, "\t;; 2 i64 %" PRIi64, sasm.prog.instructions[i].operand2.i64);
        if(sasm.prog.instructions[i].operand2.f64!=0)
        fprintf(f, "\t;; 2 f64 %lf"     , sasm.prog.instructions[i].operand2.f64);
    
        fprintf(f, "\n");
    }

    return 0;
}

void processFlag(Sasm* sasm, const char* program, const char* flag, int* argc, char*** argv)
{
    switch (flag[1]) {
    case 'i':
        inputFile = getNextCmdLineArg(argc, argv);
        return;
    case 'o':
        outputFile = getNextCmdLineArg(argc, argv);
        return;
    case 'I':
        pushIncludePath(sasm, getNextCmdLineArg(argc, argv));
        return;
    case 'd':
        disassemblyMode = true;
        return;
    default:
        fprintf(stdout, "Usage: %s -i <input.sasm> -o <output.sm>\n", program);
        displayMsgWithExit("Unknown option provided.");
    }
}