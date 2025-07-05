The following opcodes are used for **Modulus**:

- MODI — Mod by Signed Integer
- MODU — Mod by Unsigned Integer

---

### MODI — _Mod by Signed Integer_ {#MODI}

```title="Algorithm"
    L2 = L2 % <signed_imm>
    L2 = L2 % <reg_val>
    L2 = L2 % <const>

```

<div class="result" markdown>

=== "MODI Example"

    ```linenums="1" hl_lines="1 3 5"
        ; imm +ve
            MODI    1
        ; imm -ve
            MODI    -123
        ; reg val
            MODI    val(QT)
        ; const
            MODI    SOME_CONST_VAL

    ```

=== "MODI Properties"

    | Opcode | Operand Type          | Destination   |
    |--------|-----------------------|---------------|
    | 17     | Signed 64-bit integer | L2 (implicit) |

</div>

### MODU — _Mod by Unsigned Integer_ {#MODU}

```title="Algorithm"
    L3 = L3 % <unsigned_imm>
    L3 = L3 % <reg_val>
    L3 = L3 % <const>

```

<div class="result" markdown>

=== "MODU Example"

    ```linenums="1" hl_lines="1 3 5"
        ; imm +ve
            MODU    1
        ; reg val
            MODU    val(QT)
        ; const
            MODU    SOME_CONST_VAL

    ```

=== "MODU Properties"

    | Opcode | Operand Type          | Destination   |
    |--------|-----------------------|---------------|
    | 22     | Unsigned 64-bit value | L3 (implicit) |

</div>

---
