
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

---

Let me know if you want this broken up into modular sections (e.g., About, Features, Tooling, Get Started) or if you're using `partials` and need it styled for a specific homepage layout.
