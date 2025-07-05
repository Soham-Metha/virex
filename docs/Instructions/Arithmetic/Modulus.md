The following opcodes are used for **Modulus**:

- MODI — Mod by Signed Integer
- MODU — Mod by Unsigned Integer

---

??? note "MODI — _Mod by Signed Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 17                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Signed 64-bit integer     |
        | **Destination** | `L2` (implicit)           |

    === "Algorithm"

        ```
        L2 = L2 % <signed_imm>
        L2 = L2 % <reg_val>
        L2 = L2 % <const>
        ```

    === "Example"

        ```
        ; imm +ve
            MODI    1
        ; imm -ve
            MODI    -123
        ; reg val
            MODI    val(QT)
        ; const
            MODI    SOME_CONST_VAL
        ```

??? abstract "MODU — _Mod by Unsigned Integer_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      | 22                        |
        | **Type**        | Arithmetic                |
        | **Operand Type**| Unsigned 64-bit value     |
        | **Destination** | `L3` (implicit)           |

    === "Algorithm"

        ```
        L3 = L3 % <unsigned_imm>
        L3 = L3 % <reg_val>
        L3 = L3 % <const>
        ```

    === "Example"

        ```
        ; imm +ve
            MODU    1
        ; reg val
            MODU    val(QT)
        ; const
            MODU    SOME_CONST_VAL

        ```
