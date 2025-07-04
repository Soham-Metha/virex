# 🧠 Instruction Set

> **Version**: `0.5.0`  
> **Total Instructions Supported**: `73`  
> **Operand Size**: Up to **2 operands**, each of **64-bits**

---

## 🧩 Operand Types

Instructions in SASM accept a variety of operand types:

??? example "Immediate Values"

    0, 1, 2, 3

??? example "Constants"

    M, N, O, P

??? example "Registers"

    L0, L1, L2, L3

---

## 🗂️ Register Dereferencing

SASM registers are identified by **unique IDs**. Each register can be accessed either as a **reference** or as a **value** using *compile-time functions*.

```sasm
ref(L1)  ; reference to register L1
val(L1)  ; value stored in register L1
```

> These are **compile-time functions** that tell the assembler how to interpret operands.

---

## 🔗 Related References

* 📄 [Compile-time Functions](../reference/compile_time_functions.md) <!-- Update this link -->
* 📄 [Register Reference](../reference/registers.md) <!-- Update this link -->

### INSTRUCTION DOCUMENTATION TEMPLATE:

??? abstract "[MEMONIC] — _[Operation]_"

    === "Properties"

        | Property        | Value                     |
        |-----------------|---------------------------|
        | **Opcode**      |      |
        | **Type**        |      |
        | **Operand Type**|      |
        | **Destination** |      |

    === "Algorithm"

        ```
        [ALGO]
        ```

    === "Example"

        ```
            [EXAMPLE]
        ```


### INSTRUCTIONS NOT DOCUMENTED:

    INST_DONOP,
    INST_INVOK,
    INST_RETVL,
    INST_PUSHR,
    INST_SPOPR,
    INST_SHUTS,
    INST_SETR,
    INST_GETR,
    INST_CALL,
    INST_LOOP,
    INST_PUSH,
    INST_SPOP,
    INST_SWAP,

    INST_JMPU,
    INST_JMPC,
    INST_ANDB,
    INST_NOTB,
    INST_COPY,
    INST_DUPS,
    INST_RET,
    INST_NOT,
    INST_EQI,
    INST_GEI,
    INST_GTI,
    INST_LEI,
    INST_LTI,
    INST_NEI,
    INST_EQU,
    INST_GEU,
    INST_GTU,
    INST_LEU,
    INST_LTU,
    INST_NEU,
    INST_EQF,
    INST_GEF,
    INST_GTF,
    INST_LEF,
    INST_LTF,
    INST_NEF,
    INST_ORB,
    INST_XOR,
    INST_SHR,
    INST_SHL,
    INST_I2F,
    INST_U2F,
    INST_F2I,
    INST_F2U,
    INST_READ1U,
    INST_READ2U,
    INST_READ4U,
    INST_READ8U,
    INST_READ1I,
    INST_READ2I,
    INST_READ4I,
    INST_READ8I,
    INST_WRITE1,
    INST_WRITE2,
    INST_WRITE4,
    INST_WRITE8,