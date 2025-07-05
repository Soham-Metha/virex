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

SASM registers are identified by **unique IDs**. Each register can be accessed either as a **reference** or as a **value** using _compile-time functions_.

```sasm
ref(L1)  ; reference to register L1
val(L1)  ; value stored in register L1
```

> These are **compile-time functions** that tell the assembler how to interpret operands.

---

### 🔗 Related References

- 📄 [Compile-time Functions](../reference/compile_time_functions.md) <!-- Update this link -->
- 📄 [Register Reference](../reference/registers.md) <!-- Update this link -->

## Instruction Set - Quick Reference

=== "ARITHMETIC"

    === "INTEGER"

        | OPCODE | INST |
        |--------|------|
        | **13** | [ADDI](Arithmetic/Addition.md#ADDI) |
        | **14** | [SUBI](Arithmetic/Subtraction.md#SUBI) |
        | **15** | [MULI](Arithmetic/Multiplication.md#MULI) |
        | **16** | [DIVI](Arithmetic/Division.md#DIVI) |
        | **17** | [MODI](Arithmetic/Modulus.md#MODI) |

    === "UNSIGNED"

        | OPCODE | INST |
        |--------|------|
        | **18** | [ADDU](Arithmetic/Addition.md#ADDU) |
        | **19** | [SUBU](Arithmetic/Subtraction.md#SUBU) |
        | **20** | [MULU](Arithmetic/Multiplication.md#MULU) |
        | **21** | [DIVU](Arithmetic/Division.md#DIVU) |
        | **22** | [MODU](Arithmetic/Modulus.md#MODU) |

    === "FLOAT"

        | OPCODE | INST |
        |--------|------|
        | **23** | [ADDF](Arithmetic/Addition.md#ADDF) |
        | **24** | [SUBF](Arithmetic/Subtraction.md#SUBF) |
        | **25** | [MULF](Arithmetic/Multiplication.md#MULF) |
        | **26** | [DIVF](Arithmetic/Division.md#DIVF) |

=== "UNDOCUMENTED"

    === "RELATIONAL"

        === "INTEGER"

            | OPCODE | INST |
            |--------|------|
            | **35** | [EQI](../reference/missing#TO_BE_IMPLEMENTED) |
            | **36** | [GEI](../reference/missing#TO_BE_IMPLEMENTED) |
            | **37** | [GTI](../reference/missing#TO_BE_IMPLEMENTED) |
            | **38** | [LEI](../reference/missing#TO_BE_IMPLEMENTED) |
            | **39** | [LTI](../reference/missing#TO_BE_IMPLEMENTED) |
            | **40** | [NEI](../reference/missing#TO_BE_IMPLEMENTED) |

        === "UNSIGNED"

            | OPCODE | INST |
            |--------|------|
            | **41** | [EQU](../reference/missing#TO_BE_IMPLEMENTED) |
            | **42** | [GEU](../reference/missing#TO_BE_IMPLEMENTED) |
            | **43** | [GTU](../reference/missing#TO_BE_IMPLEMENTED) |
            | **44** | [LEU](../reference/missing#TO_BE_IMPLEMENTED) |
            | **45** | [LTU](../reference/missing#TO_BE_IMPLEMENTED) |
            | **46** | [NEU](../reference/missing#TO_BE_IMPLEMENTED) |

        === "FLOAT"

            | OPCODE | INST |
            |--------|------|
            | **47** | [EQF](../reference/missing#TO_BE_IMPLEMENTED) |
            | **48** | [GEF](../reference/missing#TO_BE_IMPLEMENTED) |
            | **49** | [GTF](../reference/missing#TO_BE_IMPLEMENTED) |
            | **50** | [LEF](../reference/missing#TO_BE_IMPLEMENTED) |
            | **51** | [LTF](../reference/missing#TO_BE_IMPLEMENTED) |
            | **52** | [NEF](../reference/missing#TO_BE_IMPLEMENTED) |

    === "TYPE CASTING"

        | OPCODE | INST |
        |--------|------|
        | **57** | [I2F](../reference/missing#TO_BE_IMPLEMENTED) |
        | **58** | [U2F](../reference/missing#TO_BE_IMPLEMENTED) |
        | **59** | [F2I](../reference/missing#TO_BE_IMPLEMENTED) |
        | **60** | [F2U](../reference/missing#TO_BE_IMPLEMENTED) |

    === "MEMORY ACCESS"

        | OPCODE | INST |
        |--------|------|
        | **61** | [READ1U](../reference/missing#TO_BE_IMPLEMENTED) |
        | **62** | [READ2U](../reference/missing#TO_BE_IMPLEMENTED) |
        | **63** | [READ4U](../reference/missing#TO_BE_IMPLEMENTED) |
        | **64** | [READ8U](../reference/missing#TO_BE_IMPLEMENTED) |
        | **65** | [READ1I](../reference/missing#TO_BE_IMPLEMENTED) |
        | **66** | [READ2I](../reference/missing#TO_BE_IMPLEMENTED) |
        | **67** | [READ4I](../reference/missing#TO_BE_IMPLEMENTED) |
        | **68** | [READ8I](../reference/missing#TO_BE_IMPLEMENTED) |
        | **69** | [WRITE1](../reference/missing#TO_BE_IMPLEMENTED) |
        | **70** | [WRITE2](../reference/missing#TO_BE_IMPLEMENTED) |
        | **71** | [WRITE4](../reference/missing#TO_BE_IMPLEMENTED) |
        | **72** | [WRITE8](../reference/missing#TO_BE_IMPLEMENTED) |

    === "SEQUENCE CONTROL"

        | OPCODE | INST |
        |--------|------|
        |  **1** | [INVOK](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **2** | [RETVL](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **8** | [CALL](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **9** | [LOOP](../reference/missing#TO_BE_IMPLEMENTED) |
        | **27** | [JMPU](../reference/missing#TO_BE_IMPLEMENTED) |
        | **28** | [JMPC](../reference/missing#TO_BE_IMPLEMENTED) |
        | **33** | [RET](../reference/missing#TO_BE_IMPLEMENTED) |

    === "BINARY OPERATIONS"

        | OPCODE | INST |
        |--------|------|
        | **34** | [NOT](../reference/missing#TO_BE_IMPLEMENTED) |
        | **53** | [ORB](../reference/missing#TO_BE_IMPLEMENTED) |
        | **54** | [XOR](../reference/missing#TO_BE_IMPLEMENTED) |
        | **55** | [SHR](../reference/missing#TO_BE_IMPLEMENTED) |
        | **56** | [SHL](../reference/missing#TO_BE_IMPLEMENTED) |
        | **29** | [ANDB](../reference/missing#TO_BE_IMPLEMENTED) |
        | **30** | [NOTB](../reference/missing#TO_BE_IMPLEMENTED) |

    === "MISC"

        | OPCODE | INST |
        |--------|------|
        |  **0** | [DONOP](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **3** | [PUSHR](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **4** | [SPOPR](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **5** | [SHUTS](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **6** | [SETR](../reference/missing#TO_BE_IMPLEMENTED) |
        |  **7** | [GETR](../reference/missing#TO_BE_IMPLEMENTED) |
        | **10** | [PUSH](../reference/missing#TO_BE_IMPLEMENTED) |
        | **11** | [SPOP](../reference/missing#TO_BE_IMPLEMENTED) |
        | **12** | [SWAP](../reference/missing#TO_BE_IMPLEMENTED) |
        | **31** | [COPY](../reference/missing#TO_BE_IMPLEMENTED) |
        | **32** | [DUPS](../reference/missing#TO_BE_IMPLEMENTED) |

## INSTRUCTION DOCUMENTATION TEMPLATE:

### [OPCODE] — _[OPERATION]_ {#[OPCODE]}

```title="Algorithm"

```

<div class="result" markdown>

=== "[OPCODE] Example"

    ```linenums="1" hl_lines="1 3 5"

    ```

=== "[OPCODE] Properties"

    | Opcode | Operand Type       | Destination   |
    |--------|--------------------|---------------|
    | 00     | 64-bit       Value | L_ (implicit) |

    Identified as memonic [#[OPCODE]](#[OPCODE]), [OPCODE] is used to

</div>
