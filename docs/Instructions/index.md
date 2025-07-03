# Instruction Set

As of ver. `0.5.0`, SASM has support for 73 instructions!

Each instruction can have upto 2 operands, each 64-bits in size.

!!! Example "The operands can be either immediate values."

    0,1,2,3

!!! Example "Or they can be constants"

    M,N,O,P

!!! Example "Or Registers."

    L0,L1,L2,L3

## Registers

Registers in SASM are identified by unique IDs, with each register having its own.

Registers are addressed as either `references` or `values` via `compile-time functions`, namely ref() and val()

SEE {REFERENCE}

### REFERENCE NEEDED `compile-time functions`
### REFERENCE NEEDED `registers`