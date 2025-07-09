=== "VIREX"

    VIREX is a lightweight, educational virtual machine designed for clarity, customizability, and systems programming exploration.

    === "Core"

        !!! info ""

            🧠 Core VM Features
            !!! warning ""


            !!! danger inline ""

                Custom Instruction Set

                Hybrid Architecture (Stack + Registers)

                Memory Management

                Region-Based Memory Management (WIP)

            !!! warning ""

            The VIREX Virtual Machine implements a compact instruction set capable of handling control flow, arithmetic, logic, memory operations, and I/O.

            It follows a hybrid architecture that combines a traditional register set with stack-based operations.

            RAM is simulated for direct memory manipulation, and an experimental region-based memory management system (based on linked lists) is currently under development to support efficient allocation and deallocation.

            !!! warning ""

            !!! example ""

                Current Status:

                Implementation of Region-
                Based Memory Management
                done, but not yet integrated
                completely.

    === "Interfaces and Integration"

        !!! info ""

            🖥️ Interface & Integration
            !!! warning ""
            !!! danger inline ""

                - Portable C Implementation
                - Interactive Execution Modes
                - Modular Output System
                - Built-in Debug Visuals
                - Customizable Callbacks(WIP)
                - Plugin-Friendly Architecture(WIP)

            !!! warning ""

            Clean ANSI C99 codebase with minimal dependencies.

            VIREX provides rich debugging capabilities with interactive step-by-step execution, making it ideal for inspecting program behavior.

            Its modular UI includes live-updating windows for output, memory state, and instruction traces.

            The debug visuals make it easy to understand internal state changes during execution.

            CLI, GUI, or other UIs can be built around the exposed interfaces due to the plugin nature.

            Developers can also inject custom callbacks after each instruction cycle to enable advanced features like profiling or visualization.

            !!! warning ""

            !!! example ""

                Current Status:

                Still in Ideation/Planning phase, the Region-Based memory allocation,
                TUI and AST may be separated into individual plugins in future.

=== "SASM"

    SASM is the assembler that compiles human-readable `.sasm` source code into binary files executable by VIREX.

    === "Assembly Workflow"


        !!! info ""

            🧵 Parsing & Assembly Workflow
            !!! warning ""


            !!! danger inline ""

                Rule-Based Parser

                Custom AST

                Multi-Stage Compilation Pipeline

                Custom Executable

                Compile-Time Evaluation Support (len(), ref(), value(), res())

            !!! warning ""

            SASM employs a rule-based parsing system that strictly separates files into well-defined stages: file, line, statement, and expression parsing.

            After this process, a custom Abstract Syntax Tree (AST) is constructed, allowing deeper insights into source structure.

            The assembler supports compile-time evaluation with functions like len("string"), ref(reg), and others, enabling more expressive assembly code. Final output is generated as VIREX-compatible `.sm` binaries, completing the clean multi-stage compilation flow.

            !!! warning ""

    === "Modular & Advanced"


        !!! info ""

            🧩 Modular & Advanced Features
            !!! warning ""
            !!! danger inline ""

                Assembly Directives like 'include', 'bind', 'scope' and 'entry'

                Constant and Label Definitions

                Operand Intent Detection

                Educational Architecture


            !!! warning ""

            SASM supports modular assembly development with features like the include directive for file composition and symbolic definitions for constants, labels, enabling clear, maintainable code.

            It also provides directives like scope for local scoping and entry whuch identifies the entry point.

            Advanced capabilities include operand intent detection at compile time using evaluation functions, allowing smart resolution of operand types.

            Designed with clarity and structure, SASM is ideal for educational use in understanding assembler internals and low-level compilation workflows.

            !!! warning ""
