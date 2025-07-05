
The following opcodes are used for **Division**:

- DIVI — Divide by Signed Integer
- DIVU — Divide by Unsigned Integer
- DIVF — Divide by Floating Point

---

??? abstract "DIVI — _Divide by Signed Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 16                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Signed 64-bit integer     |
        | **Destination** | `L2` (implicit)           |

    === "Algorithm"

        ```
        L2 = L2 / <signed_imm>
        L2 = L2 / <reg_val>
        L2 = L2 / <const>
        ```

    === "Example"

        ```
        ; imm +ve
            DIVI    1
        ; imm -ve
            DIVI    -123
        ; reg val
            DIVI    val(QT)
        ; const
            DIVI    SOME_CONST_VAL
        ```

??? abstract "DIVU — _Divide by Unsigned Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 21                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Unsigned 64-bit value     |
        | **Destination** | `L3` (implicit)           |

    === "Algorithm"

        ```
        L3 = L3 / <unsigned_imm>
        L3 = L3 / <reg_val>
        L3 = L3 / <const>
        ```

    === "Example"

        ```
        ; imm +ve
            DIVU    1
        ; reg val
            DIVU    val(QT)
        ; const
            DIVU    SOME_CONST_VAL

        ```

??? abstract "DIVF — _Divide by Float value_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 26                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| 64-bit float value        |
        | **Destination** | `L1` (implicit)           |

    === "Algorithm"

        ```
        L1 = L1 / <float>
        L1 = L1 / <reg_val>
        L1 = L1 / <const>
        ```

    === "Example"

        ```
        ; imm float
            DIVF    3.14
        ; reg val
            DIVF    val(QT)
        ; const
            DIVF    SOME_CONST_VAL

        ```
---