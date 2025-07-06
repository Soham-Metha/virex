<<<<<<< HEAD
---
template: home.html
title: VIREX

---


# 🧬 **VIREX** — *The VIRtual EXecuter*

**VIREX** is a portable, lightweight virtual machine that runs programs written in a custom intermediate language called **SASM** — *Simulated Assembly*. Think of it as the **JVM for your own language**, but with transparency, control, and a fully editable instruction set.

Designed to be educational and extensible, VIREX opens the door to systems-level thinking without forcing you to dive into raw x86 or ARM.

---

## 🧭 What Is SASM?

**SASM** is a human-readable assembly-like language designed to serve as the **intermediate representation (IR)** for any compiler targeting the VIREX runtime. Unlike conventional bytecode formats:

* 🟢 It's **text-based**, not binary — easy to inspect, diff, and version.
* ✏️ It's **editable by hand** — write or tweak your programs directly in SASM.
* 🧩 It's **tooling-friendly** — build compilers, assemblers, visualizers, and analyzers around it.

> If LLVM IR is too complex and raw bytecode is too opaque, SASM is your sweet spot.

---

## 🧠 Why SASM + VIREX?

Whether you're a language designer, systems programmer, or just curious how virtual machines and compilers work, SASM and VIREX provide the perfect sandbox.

Here’s what makes it special:

| Feature                  | Benefit                                                            |
| ------------------------ | ------------------------------------------------------------------ |
| **Open Instruction Set** | Customize or extend the VM with new opcodes and semantics          |
| **Portable Execution**   | Write once, run anywhere VIREX runs                                |
| **Clean Syntax**         | Designed for learning, debugging, and experimentation              |
| **Tooling Ecosystem**    | Includes assembler, AST visualizer, VS Code syntax theme, and more |
| **Compiler-Ready**       | Ideal IR target for custom languages like **ORIN**                 |

---

## 🛠️ What's Included?

VIREX isn't just a VM; it's a whole ecosystem for low-level development:

* 🧾 **SASM Assembler**: Translates `.sasm` files into VM-executable binaries.
* 🌐 **AST Visualizer**: Graphical output of the instruction flow and scope tree.
* 🎨 **VS Code Theme**: Rich syntax highlighting for SASM to improve readability.
* ⚙️ **Extensible Runtime**: Easily add new registers, memory models, or system calls.
* 🧪 **ORIN Language (WIP)**: A high-level language that compiles directly to SASM.

---

## 🔮 The Vision

> Our mission is to make systems programming **approachable**!

VIREX is designed for **education**, **experimentation**, and **language development**. By abstracting away the messiness of real hardware and binary formats, it lets you focus on:

* Designing instruction sets
* Writing your own compiler backends
* Learning how registers, stacks, and memory behave under the hood
* Debugging complex logic through visual ASTs

---

## 🤝 Get Involved

Whether you’re:

* a student learning compilers or virtual machines,
* an educator looking for hands-on systems material,
* a hacker building your own language,

VIREX welcomes contributions and collaboration. Visit our GitHub repo, try out SASM, or contribute to **ORIN** — our experimental high-level language.

> Ready to run your first virtual assembly program? [Get started →](Getting-Started.md#SETUP-ON-LINUX)
=======
# VIREX : Virtual Execution Console

**VIREX** (**VIR**tual **EX**ecuter) is a platform-independent virtual machine designed around a flexible intermediate language called **SASM** (Simulated Assembly). It’s inspired by the **Java Virtual Machine (JVM)**, but unlike JVM bytecode, SASM is **open, readable, and writable** — you can program directly in it.

## 🚀 What is SASM?

Just like Java compiles to bytecode for the JVM, any language can be compiled into SASM for VIREX. The difference is:

- SASM is **assembly-like**, human-readable, and editable.
- SASM is **open**, letting anyone build tools and languages around it.

You can even create your own programming language that compiles into SASM and runs anywhere VIREX runs — making your language instantly portable.

## 🧠 Why SASM?

- Learn how **assembly-level code** works through a clean and simplified syntax.
- Build a **compiler** without worrying about machine-level code generation.
- Make your own language **platform-independent** by targeting SASM.

## 🛠 Current Features

- ✅ **VS Code syntax highlighter** for SASM
- 🌲 **AST visualizer** for seeing how your SASM code is parsed and compiled
- 🔧 A new programming language called **ORIN** is currently under development. It is being designed to compile directly to SASM.

> If you're interested in compilers, language design, or virtual machines — **contributions are very welcome**!

---

## 📦 Project Structure

    /docs/      # Reference documentation
    /examples/  # Sample programs
    /include/   # Public headers for VM, SASM, OCC
    /src/       # Core implementation (VM, assembler, compiler)
    /tests/     # Simple Test programs written in SASM
    /tools/themes/vs_code/ # VS Code syntax highlighter
    /install.sh # Install script for linux

---

## 🧪 Getting Started (LINUX)

1. **Clone this repo:**
   ```bash
   git clone https://github.com/Soham-Metha/virex.git
   cd virex/
   ```
2. **Build the project (requires `sudo`):**
   ```bash
   ./install.sh
   ```
3. **Run an example program:**

   ```bash
   cd ./examples/SASM/
   virex
   ```

   > If the **TUI doesn't render properly**, try adjusting your **terminal font size**.

   > If that doesn't help, you can tweak layout values in **src/VM/vm_tui.c::CreateWindows()**.
   > The constants used are defined as **percentages** of the screen dimensions.

   > P.S. **kitty terminal** config, and font used, are available in `/tools`

4. **Inside VIREX, do the following:**

- Select **"Run SASM/ORIN command with custom flags"**
- Enter the following command:
  ```bash
  -i helloWorld.sasm -I ./ -o tmp.sm
  ```
  > ⌨️ use **Arrow keys** for navigation in menu.
- Select **"SASM build and exec"** by pressing **'a'**
- Enter the output filename (`tmp.sm`)

5. **Activate the syntax highlighter in VS Code**

- Open VS Code
- Press `Ctrl + Shift + P`
- Type: `Preferences: Color Theme`
- Select: `Palenight+sasm`
  > 🎨 Open any `.sasm` file in vs code to see the syntax highlighter at work!

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

### **Syntax Highlighting:**

![Image](../extras/vs_theme.png){ width="400" }

---

### **AST:**

![Image](../extras/AST_Examples/helloWorld.png)

!!! info "Local/Global Scopes"

    Each Code Block in the visualized AST represents a Scope, Block 0 being global scope.

---

### **Binary Executable:**

![Image](../extras/helloWorld_SM.png)

---

### **GUI:**

![Image](../extras/gui.png)

---

## **System Design and Architecture**

![Image](../extras/Architecture/virex_arch.png)

---

![Image](../extras/Architecture/sasm_arch.png)
![Image](../extras/Architecture/sasm_components_1.png)
![Image](../extras/Architecture/sasm_components_2.png)

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
>>>>>>> 27e174fdf8069df9b03e30c5d69c587551eff4bf

---
