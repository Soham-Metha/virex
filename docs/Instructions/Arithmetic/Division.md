The following opcodes are used for **Division**:

- DIVI — Divide by Signed Integer
- DIVU — Divide by Unsigned Integer
- DIVF — Divide by Floating Point

---

### DIVI — _Divide by Signed Integer_

```title="Algorithm"

    L2 = L2 / <signed_imm>
    L2 = L2 / <reg_val>
    L2 = L2 / <const>
```

<div class="result" markdown>

=== "DIVI Example"

    ```linenums="1" hl_lines="1 3 5 7"
    ; imm +ve
        DIVI    1
    ; imm -ve
        DIVI    -123
    ; reg val
        DIVI    val(QT)
    ; const
        DIVI    SOME_CONST_VAL
    ```

=== "DIVI Properties"

    | Opcode | Operand Type          | Destination   |
    |--------|-----------------------|---------------|
    | 16     | Signed 64-bit integer | L2 (implicit) |

    Identified as memonic [#16](#DIVI), DIVI is used to
    divide the L2 register by a 64-bit signed value

</div>

### DIVU — _Divide by Unsigned Integer_

```title="Algorithm"
    L3 = L3 / <unsigned_imm>
    L3 = L3 / <reg_val>
    L3 = L3 / <const>
```

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 21                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Unsigned 64-bit value     |
        | **Destination** | `L3` (implicit)           |

<div class="result" markdown>
=== "DIVU Example"

    ```linenums="1" hl_lines="1 3 5"
    ; imm +ve
        DIVU    1
    ; reg val
        DIVU    val(QT)
    ; const
        DIVU    SOME_CONST_VAL
    ```

=== "DIVU Properties"

    | Opcode | Operand Type            | Destination   |
    |--------|-------------------------|---------------|
    | 21     | Unsigned 64-bit integer | L3 (implicit) |

    Identified as memonic [#18](#DIVU), DIVU is used to
    divide the L3 register by a 64-bit unsigned value

</div>

### DIVF — _Divide by Float value_

```title="Algorithm"
    L1 = L1 / <float>
    L1 = L1 / <reg_val>
    L1 = L1 / <const>
```

<div class="result" markdown>

=== "DIVF Example"

    ```linenums="1" hl_lines="1 3 5"
    ; imm float
        DIVF    3.14
    ; reg val
        DIVF    val(QT)
    ; const
        DIVF    SOME_CONST_VAL

    ```

=== "DIVF Properties"

    | Opcode | Operand Type       | Destination   |
    |--------|--------------------|---------------|
    | 26     | 64-bit Float Value | L1 (implicit) |

    Identified as memonic [#23](#DIVF), DIVF is used to
    divide the L1 register by a 64-bit float value

---
