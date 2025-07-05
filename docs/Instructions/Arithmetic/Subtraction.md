The following opcodes are used for **subtraction**:

- SUBI — Subtract Signed Integer
- SUBU — Subtract Unsigned Integer
- SUBF — Subtract Floating Point

---

### [SUBI] — _Sub Signed Integer_ {#SUBI}

```title="Algorithm"
    L2 = L2 - <signed_imm>
    L2 = L2 - <reg_val>
    L2 = L2 - <const>

```

<div class="result" markdown>

=== "SUBI Example"

    ```linenums="1" hl_lines="1 3 5 7"
        ; imm +ve
            SUBI    1
        ; imm -ve
            SUBI    -123
        ; reg val
            SUBI    val(QT)
        ; const
            SUBI    SOME_CONST_VAL

    ```

=== "SUBI Properties"

    | Opcode | Operand Type          | Destination   |
    |--------|-----------------------|---------------|
    | 14     | Signed 64-bit integer | L2 (implicit) |

    Identified as memonic [#SUBI](#SUBI), SUBI is used to
    subtract a 64-bit signed value from the L2 register

</div>

### SUBU — _Sub Unsigned Integer_ {#SUBU}

```title="Algorithm"
    L3 = L3 - <unsigned_imm>
    L3 = L3 - <reg_val>
    L3 = L3 - <const>

```

<div class="result" markdown>

=== "SUBU Example"

    ```linenums="1" hl_lines="1 3 5"
        ; imm +ve
            SUBU    1
        ; reg val
            SUBU    val(QT)
        ; const
            SUBU    SOME_CONST_VAL

    ```

=== "SUBU Properties"

    | Opcode | Operand Type          | Destination   |
    |--------|-----------------------|---------------|
    | 19     | Unsigned 64-bit value | L3 (implicit) |

    Identified as memonic [#SUBU](#SUBU), SUBU is used to
    subtract a 64-bit unsigned value  from the L3 register

</div>
### SUBF — _Sub Float value_ {#SUBF}

```title="Algorithm"
    L1 = L1 - <float>
    L1 = L1 - <reg_val>
    L1 = L1 - <const>

```

<div class="result" markdown>

=== "SUBF Example"

    ```linenums="1" hl_lines="1 3 5"
        ; imm float
            SUBF    3.14
        ; reg val
            SUBF    val(QT)
        ; const
            SUBF    SOME_CONST_VAL
    ```

=== "SUBF Properties"

    | Opcode | Operand Type       | Destination   |
    |--------|--------------------|---------------|
    | 24     | 64-bit Float Value | L1 (implicit) |

    Identified as memonic [#SUBF](#SUBF), SUBF is used to
    subtract a 64-bit floating point value from the L1 register

</div>

---
