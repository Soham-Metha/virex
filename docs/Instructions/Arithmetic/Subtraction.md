
The following opcodes are used for **subtraction**:

- SUBI — Subtract Signed Integer
- SUBU — Subtract Unsigned Integer
- SUBF — Subtract Floating Point

---

??? abstract "SUBI — _Sub Signed Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 14                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Signed 64-bit integer     |
        | **Destination** | `L2` (implicit)           |

    === "Algorithm"

        ```
        L2 = L2 - <signed_imm>
        L2 = L2 - <reg_val>
        L2 = L2 - <const>
        ```

    === "Example"

        ```
        ; imm +ve
            SUBI    1
        ; imm -ve
            SUBI    -123
        ; reg val
            SUBI    val(QT)
        ; const
            SUBI    SOME_CONST_VAL
        ```

??? abstract "SUBU — _Sub Unsigned Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 19                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Unsigned 64-bit value     |
        | **Destination** | `L3` (implicit)           |

    === "Algorithm"

        ```
        L3 = L3 - <unsigned_imm>
        L3 = L3 - <reg_val>
        L3 = L3 - <const>
        ```

    === "Example"

        ```
        ; imm +ve
            SUBU    1
        ; reg val
            SUBU    val(QT)
        ; const
            SUBU    SOME_CONST_VAL

        ```

??? abstract "SUBF — _Sub Float value_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 24                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| 64-bit float value        |
        | **Destination** | `L1` (implicit)           |

    === "Algorithm"

        ```
        L1 = L1 - <float>
        L1 = L1 - <reg_val>
        L1 = L1 - <const>
        ```

    === "Example"

        ```
        ; imm float
            SUBF    3.14
        ; reg val
            SUBF    val(QT)
        ; const
            SUBF    SOME_CONST_VAL

        ```
---