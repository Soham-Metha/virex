
The following opcodes are used for **multiplicaction**:

- MULI — Multiply Signed Integer
- MULU — Multiply Unsigned Integer
- MULF — Multiply Floating Point

---

??? abstract "MULI — _Multiply Signed Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 15                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Signed 64-bit integer     |
        | **Destination** | `L2` (implicit)           |

    === "Algorithm"

        ```
        L2 = L2 * <signed_imm>
        L2 = L2 * <reg_val>
        L2 = L2 * <const>
        ```

    === "Example"

        ```
        ; imm +ve
            MULI    1
        ; imm -ve
            MULI    -123
        ; reg val
            MULI    val(QT)
        ; const
            MULI    SOME_CONST_VAL
        ```

??? abstract "MULU — _Multiply Unsigned Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 20                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Unsigned 64-bit value     |
        | **Destination** | `L3` (implicit)           |

    === "Algorithm"

        ```
        L3 = L3 * <unsigned_imm>
        L3 = L3 * <reg_val>
        L3 = L3 * <const>
        ```

    === "Example"

        ```
        ; imm +ve
            MULU    1
        ; reg val
            MULU    val(QT)
        ; const
            MULU    SOME_CONST_VAL

        ```

??? abstract "MULF — _Multiply Float value_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 25                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| 64-bit float value        |
        | **Destination** | `L1` (implicit)           |

    === "Algorithm"

        ```
        L1 = L1 * <float>
        L1 = L1 * <reg_val>
        L1 = L1 * <const>
        ```

    === "Example"

        ```
        ; imm float
            MULF    3.14
        ; reg val
            MULF    val(QT)
        ; const
            MULF    SOME_CONST_VAL

        ```
---