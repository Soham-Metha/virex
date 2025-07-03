# Instruction Set

As of ver. `0.5.0`, SASM has support for 73 instructions!

Each instruction can have upto 2 operands, each 64-bits in size.

The operands can be either immediate values.

!!! Example

    0,1,2,3

Or they can be constants

!!! Example

    M,N,O,P

Or Registers.

## Registers

Registers in SASM are identified by unique IDs, with each register having its own.

Registers are addressed as either `references` or `values` via `compile-time functions`, namely ref() and val()

SEE {REFERENCE}

### REFERENCE NEEDED `compile-time functions`
### REFERENCE NEEDED `registers`