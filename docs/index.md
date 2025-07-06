---
template: home.html
title: VIREX
social:
  cards_layout_options:
    title: VIRtual EXecutor

hide:
  - toc

---


**VIREX** (VIRtual EXecuter) is a platform-independent virtual machine designed around a flexible intermediate language called **SASM** (Simulated Assembly). It’s inspired by the **Java Virtual Machine (JVM)**, but unlike JVM bytecode, SASM is **open, readable, and writable** — you can program directly in it.

## 🚀 What is SASM?

Just like Java compiles to bytecode for the JVM, any language can be compiled into SASM for VIREX. The difference is:

- SASM is **assembly-like**, human-readable, and editable.
- SASM is **open**, letting anyone build tools and languages around it.

You can even create your own programming language that compiles into SASM and runs anywhere VIREX runs — making your language instantly portable.

## 🧠 Why SASM?

- Learn how **assembly-level code** works through a clean and simplified syntax.
- Build a **compiler** without worrying about machine-level code generation.
- Make your own language **platform-independent** by targeting SASM.

---

## 📦 Project Structure

    /docs/                    # Reference documentation
    /examples/                # Sample programs
    /include/                 # Public headers for VM, SASM, OCC
    /src/                     # Core implementation (VM, assembler, compiler)
    /tests/                   # Simple Test programs written in SASM
    /tools/themes/vs_code/    # VS Code syntax highlighter
    /install.sh               # Install script for linux

---

## 💡 **Want to Contribute?**

**We’re actively building:**

1. The **ORIN programming language**
2. Improved **SASM tooling** (UI, debuggers, optimizers, etc.)
3. Expanded **[Documentation](https://virex.readthedocs.io/en/latest/)** and **tutorials**

!!! info inline end  ""

    📌 For contribution guidelines and a roadmap, see [CONTRIBUTING.md]() (coming soon).

---

## **Examples**

---

### **Binary Executable:**

![Image](assets/helloWorld_SM.png)

---

### **GUI:**

![Image](assets/gui.png)

---

## **System Design and Architecture**

![Image](assets/Architecture/virex_arch.png)

---

![Image](assets/Architecture/sasm_arch.png)
![Image](assets/Architecture/sasm_components_1.png)
![Image](assets/Architecture/sasm_components_2.png)

---

## Tech Stack

- **Programming Language:** C
- **Version Control:** Git
- **Build System:** GNU Make
- **AST VISUALIZER:** Graphviz

---

## Maintainers

| Tool                    | Maintainer   |
| ----------------------- | ------------ |
| **VIREX, SASM**         | Soham Metha  |
| **AST visualizer**      | Soham Metha  |
| **Syntax Highlighter**  | Soham Metha  |
| **ORIN Compiler**       | Omkar Jagtap |
| **Core lib(Hashtable)** | Omkar Jagtap |
| **Core libs(other)**    | Soham Metha  |

---

## References

- [Tsoding](https://www.youtube.com/playlist?list=PLpM-Dvs8t0VY73ytTCQqgvgCWttV3m8LM)
- [Dr Birch](https://www.youtube.com/@dr-Jonas-Birch)
- [Low Byte Productions](https://www.youtube.com/playlist?list=PLP29wDx6QmW5DdwpdwHCRJsEubS5NrQ9b)
- [Cobb Coding](https://www.youtube.com/playlist?list=PLRnI_2_ZWhtCxHQ_3zDfW0-RgiWo8ftyj)

---
