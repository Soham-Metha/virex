---
hide:
  - toc
---

## Tech Stack

- **Programming Language:** C
- **Version Control:** Git
- **Build System:** GNU Make
- **AST VISUALIZER:** Graphviz

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
## Architecture

### VIREX

![Image](assets/Architecture/virex_arch.png)

---

### SASM

![Image](assets/Architecture/sasm_arch.png)

### Individual Components of SASM
![Image](assets/Architecture/sasm_components_1.png)
![Image](assets/Architecture/sasm_components_2.png)

---
