#include "virex_assembler.h"
#include "virex_ui.h"

void processFlag(const char *program, const char *flag, int *argc, char ***argv);
void inputHandler(Vm *vm, int *highlight);
void __exec_sm(Vm *vm);
void __assemble_sasm();
void __disassemble_sm();

const char *inputFile = NULL;
const char *outputFile = NULL;
char buffer[256];
int limit = -1;
int debug = 0;

int main(int argc, char **argv)
{
    static Vm vm = {0};
    loadStandardCallsIntoVm(&vm);
    OnStart();

    const char *program = getNextCmdLineArg(&argc, &argv);

    while (argc > 0)
    {
        const char *flag = getNextCmdLineArg(&argc, &argv);
        processFlag(program, flag, &argc, &argv);
    }

    int highlight = 0;
    do
    {
        highlight = getUserInput();

        inputHandler(&vm, &highlight);
        OnPause();

        setReg(REG_NX, &vm, 0);
        setFlag(META_HALT, &vm.cpu, 0);

    } while (true);
    return 0;
}

void processFlag(const char *program, const char *flag, int *argc, char ***argv)
{

    switch (flag[1])
    {
    case 'l':
        limit = atoi(getNextCmdLineArg(argc, argv));
        return;
    default:
        fprintf(stdout, "Usage: %s  [-l <limit>]\n", program);
        displayMsgWithExit("Unknown option provided.");
    }
}

void inputHandler(Vm *vm, int *highlight)
{
    clearWindow(INPUT);
    refreshAllWindows();
    moveCursorWithinWindow(INPUT, 2, 4);
    switch (*highlight)
    {
    case EXEC_SM:
        readFilePath(INPUT, "Enter the name of the SM file : ", &inputFile);
        __exec_sm(vm);
        break;
    case CUSTOM_CMD:
        readFilePath(INPUT, "Enter command(no need to specify sasm/orin) : ", &outputFile);
        printOut(INPUT, "\n     (S) SASM build"
                        "\n     (O) ORIN build"
                        "\n     (A) SASM build and exec"
                        "\n     (C) ORIN Build and exec"
                        "\n         Default: (A)"
                        "\n         Your choice? : ");
        refreshAllWindows();
        char ch = getChar(INPUT);
        if (ch == 'o' || ch == 'O' || ch == 'c' || ch == 'C')
        {
            // snprintf(buffer, sizeof(buffer), "orin %s", outputFile);
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "sasm %s", outputFile);
        }
        if (system(buffer) != 0)
        {
            displayMsgWithExit("Assembly Failed");
        }
        if (ch != 'o' && ch != 'O' && ch != 'c' && ch != 'C' && ch != 'S' && ch != 'C')
        {
            clearWindow(INPUT);
            refreshAllWindows();
            moveCursorWithinWindow(INPUT, 2, 4);
            readFilePath(INPUT, "Enter the name of the SM file : ", &inputFile);
            __exec_sm(vm);
        }
        break;

    case ASSEMBLE_EXEC_SASM:
        __assemble_sasm();
        moveCursorWithinWindow(INPUT, 4, 4);
        inputFile = outputFile;
        __exec_sm(vm);
        break;

    case ASSEMBLE_SASM:
        __assemble_sasm();
        break;

    case DISASSEMBLE_SM:
        __disassemble_sm();
        break;

    case COMPILE_ORIN:
    case EXIT_VM:
        OnExit();
    default:
        break;
    }
}

void __exec_sm(Vm *vm)
{
    loadProgramIntoVm(vm, inputFile);

    printOut(INPUT, "\n     Debug Mode?"
                    "\n     0. No"
                    "\n     1. Yes"
                    "\n     2. Fast Debug"
                    "\n     Your choice : ");
    refreshAllWindows();

    debug = getChar(INPUT) - '0';
    if (debug == 0)
        debug = 2;
    executeProgram(vm, debug, -1);
}

void __assemble_sasm()
{
    readFilePath(INPUT, "Enter the name of the SASM file : ", &inputFile);
    moveCursorWithinWindow(INPUT, 3, 4);
    readFilePath(INPUT, "Enter the name of the output SM file : ", &outputFile);

    snprintf(buffer, sizeof(buffer), "sasm -i %s -o %s", inputFile, outputFile);

    if (system(buffer) != 0)
    {
        displayMsgWithExit("Assembly Failed");
    }
}

void __disassemble_sm()
{
    readFilePath(INPUT, "Enter the name of the SM file : ", &inputFile);
    moveCursorWithinWindow(INPUT, 3, 4);
    readFilePath(INPUT, "Enter the name of the output SASM file : ", &outputFile);

    snprintf(buffer, sizeof(buffer), "sasm -i %s -o %s -d", inputFile, outputFile);

    if (system(buffer) != 0)
    {
        displayMsgWithExit("Disassembly Failed");
    }
}