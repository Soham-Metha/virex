## Arithmetic

This section describes the available arithmetic opcodes/memonics and their corresponding operations.

All the arithmetic instructions accept only a single operand.
The other operand(also the destination) is taken from the Link register L0, L1, L2, L3

SEE {REFERENCE}

### REFERENCE NEEDED `registers-Link_registers`

### Addition

The addition instructions are
    - ADDI (ADD Integer)
    - ADDU (ADD Unsigned)
    - ADDF (ADD Floating point values)

1. ADDI:
    Opcode: 13
    Operand Accepted: 64-bit signed integers
    Adds the passed 64-bit signed int value to the value stored in the register L2(also considered to be an 64-bit signed integer value)
    The result is stored in the L2 Register

!!! Example

    ADDI 1 ;Will add 1 to whatever value is in register L2

| **Opcode** | **Code**    |**Operand Count** | **Opernads**           | **Description**                     |
| SUBI |  |
| MULI |  |
| DIVI |  |
| MODI |  |
| ADDU |  |
| SUBU |  |
| MULU |  |
| DIVU |  |
| MODU |  |
| ADDF |  |
| SUBF |  |
| MULF |  |
| DIVF |  |