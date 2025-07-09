🧠 Register Set (VIREX VM)

The VIREX virtual machine provides a fixed set of general-purpose and special-purpose registers, each designed to support specific roles such as execution flow, memory management, I/O, or control signaling.

Although some registers are named with specialized roles, as of version 0.5.0, only a few instructions implicitly expect specific registers. This means that in most cases, registers can be used flexibly as general-purpose storage without restriction.

!!! info ""

    Registers are internally identified by integer IDs.<br>
    During assembly, the compile-time functions ref() and val() are used to indicate register intent, whether a reference (address) or value should be used.

    - By default, registers are interpreted as references (ref()).
    - Instructions like SETR and GETR explicitly **require register references**, not values.

=== "UNDOCUMENTED"

    | ID  | Name       | Purpose                         |
    |-----|------------|---------------------------------|
    | 0   | [H0](../reference/missing.md)   | Label Handler (primary)        |
    | 1   | [H1](../reference/missing.md)   | Label Handler (secondary)      |
    | 2   | [I0](../reference/missing.md)   | Index register 0               |
    | 3   | [I1](../reference/missing.md)   | Index register 1               |
    | 4   | [JS](../reference/missing.md)   | Journal Start / log pointer    |
    | 5   | [KC](../reference/missing.md)   | Kill Code / exit signal        |
    | 6   | [L0](../reference/missing.md)   | Link - Pointer                 |
    | 7   | [L1](../reference/missing.md)   | Link - Float value             |
    | 8   | [L2](../reference/missing.md)   | Link - Integer value           |
    | 9   | [L3](../reference/missing.md)   | Link - Unsigned integer value  |
    | 10  | [NX](../reference/missing.md)   | NeXt Instruction Pointer       |
    | 11  | [OP](../reference/missing.md)   | Output                         |
    | 12  | [P0](../reference/missing.md)   | Proxy Counter 0                |
    | 13  | [P1](../reference/missing.md)   | Proxy Counter 1                |
    | 14  | [P2](../reference/missing.md)   | Proxy Counter 2                |
    | 15  | [P3](../reference/missing.md)   | Proxy Counter 3                |
    | 16  | [QT](../reference/missing.md)   | Quantity                       |
    | 17  | [RF](../reference/missing.md)   | Reference                      |
    | 18  | [SP](../reference/missing.md)   | Stack Pointer                  |