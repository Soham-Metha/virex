### 🧠 VM Calls (VIREX Runtime Interface)

Similar to how **syscalls** allow user programs to interact with the operating system, **vmcalls** are a mechanism for communicating with the virtual machine itself. These instructions trigger **built-in functionality** provided by VIREX at runtime.

Currently, **8** vmcalls are defined and implemented, handling tasks like memory management, printing, and i/o. There is also an idea under consideration to support external [plugin-based]() vmcalls.

!!! info ""

    VM calls are executed via a specific opcode [INVOKE](../reference/missing.md) followed by the call number. A simple header file can also be created to map the vm calls to their IDs.

=== "UNDOCUMENTED"


    | Call ID | Name                             |
    |---------|----------------------------------|
    | 0       | [alloc](../reference/missing.md) |
    | 1       | [free](../reference/missing.md)  |
    | 2       | [print_f64](../reference/missing.md) |
    | 3       | [print_i64](../reference/missing.md) |
    | 4       | [print_u64](../reference/missing.md) |
    | 5       | [print_ptr](../reference/missing.md) |
    | 6       | [dump_memory](../reference/missing.md) |
    | 7       | [write](../reference/missing.md) |

