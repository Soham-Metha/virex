# VIREX : Virtual Execution Console


<!--![GSSoC Logo](/virex/docs/assets/gssoc%20logo.png) -->

[![Open Source](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/Soham-Metha) <img alt="Issues" src="https://img.shields.io/github/issues/Soham-Metha/virex?style=flat&logo=github"/> <img alt="Open Pull Requests" src="https://img.shields.io/github/issues-pr/Soham-Metha/virex?style=flat&logo=github"/> <img alt="Closed Pull Requests" src="https://img.shields.io/github/issues-pr-closed/Soham-Metha/virex?style=flat&color=critical&logo=github"/>
<!--img alt="Stars" src="https://img.shields.io/github/stars/Soham-Metha/virex?style=flat&logo=github"/> <img alt="Forks" src="https://img.shields.io/github/forks/Soham-Metha/virex?style=flat&logo=github"/-->


[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE) [![Build](https://img.shields.io/github/actions/workflow/status/Soham-Metha/virex/ci.yml)](https://github.com/Soham-Metha/virex/actions) [![Docs](https://img.shields.io/badge/docs-online-blue)](https://virex.readthedocs.io/en/latest/) [![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](CONTRIBUTING.md)

---

**VIREX** (**VIR**tual **EX**ecuter) is a platform-independent virtual machine designed around a flexible intermediate language called **SASM** (Simulated Assembly). It’s inspired by the **Java Virtual Machine (JVM)**, but unlike JVM bytecode, SASM is **open, readable, and writable** — you can program directly in it. VIREX allows you to explore VM internals, build compilers, and experiment with language design; all in C.

---

## 🚀 What is SASM?

Just like Java compiles to bytecode for the JVM, any language can be compiled into SASM for VIREX. The difference is:

- SASM is **assembly-like**, human-readable, and editable.
- SASM is **open**, letting anyone build tools and languages around it.

You can even create your own programming language that compiles into SASM and runs anywhere VIREX runs — making your language instantly portable.

This makes SASM ideal for systems programmers, compiler devs, and those learning how VMs work.

---


## 🧠 Why SASM?

- Understand **low-level systems** through a safe, abstracted virtual environment.
- Learn how **assembly-level code** works through a clean and simplified syntax.
- Build a **compiler** without worrying about machine-level code generation.
- Make your own language **platform-independent** by targeting SASM.

---


## 🛠 Current Features

- ✅ **VS Code syntax highlighter** for SASM
- 🌲 **AST visualizer** for seeing how your SASM code is parsed and compiled
- 🔧 A new programming language called **ORIN** is currently under development. It is being designed to compile directly to SASM.

> If you're interested in compilers, interpreters, language design, VMs, or systems programming, **we’d love your contributions**!

---
<!--

## 📦 Project Layout

```
/docs/            # Documentation & diagrams
/examples/        # Sample programs in SASM
/include/         # Public headers
/src/             # Core code (VM, assembler, compiler)
/tests/           # Test cases for SASM programs
/tools/themes/    # VS Code syntax highlighter and dev tools
/install.sh       # One-command installer
```

---
## 🧪 Getting Started (Linux)

> 📝 For more detailed setup and usage guides, visit [our docs »](https://virex.readthedocs.io/en/latest/)

### 1. Clone and install:

```bash
git clone https://github.com/Soham-Metha/virex.git
cd virex/
./install.sh
```

### 2. Run a demo:

```bash
cd examples/SASM/
virex
```

> If the **UI looks misaligned**, try adjusting your **terminal font size** or tweak layout values in `src/VM/vm_tui.c::CreateWindows()`.

---

## 🎨 Developer Tools

### Syntax Highlighting in VS Code

- Install from `/tools/themes/vs_code`
- Then:
  1. Open any `.sasm` file
  2. Press `Ctrl + Shift + P` → `Preferences: Color Theme` → Select `Palenight+sasm`

---

## 💡 Contributing

We’re actively working on:

- 🚧 The **ORIN** programming language (compiler -> SASM)
- 🧩 Tooling for SASM (debuggers, profilers, IDE integrations)
- 📖 Better documentation and tutorials

Want to get involved? See our [CONTRIBUTING.md](CONTRIBUTING.md) (coming soon).

---

## 🧪 Examples

### Syntax Highlighting

![Syntax Highlighting](docs/assets/vs_theme.png)

### AST Visualization

![AST](docs/assets/AST_Examples/helloWorld.png)

> Each block represents a scope. Block 0 = global scope.

### Terminal UI

![TUI](docs/assets/gui.png)

## ⚙️ Tech Stack

- **Language**: C
- **Build System**: GNU Make
- **Visualization**: Graphviz
- **Version Control**: Git

---
## 📚 More Info

<!-- ![Repo Beats](https://repobeats.axiom.co/api/embed/f97cd2b4327090163e02c14473729db0cc3051c6.svg "Repo activity insights") -->
<!--
Full documentation (including internal architecture and instruction sets) is available at:  
📖 [https://virex.readthedocs.io](https://virex.readthedocs.io/en/latest/)

---
<!--
## 📬 License

This project is licensed under the **GNU General Public License v3.0**.  
You may copy, distribute, and modify the software as long as changes remain open-source and licensed under GPL-3.0.

📄 See the full [LICENSE](LICENSE) file for details.
-->
## 💡 Suggestions & Feedback
Feel free to open issues or discussions if you have any feedback, feature suggestions, or want to collaborate!

---
## 📜 Code of Conduct

To ensure a welcoming and inclusive environment, we have a Code of Conduct that all contributors are expected to follow. In short: **Be respectful, be kind, and be collaborative.** Please read the full [Code of Conduct](https://github.com/Soham-Metha/virex/blob/main/CODE_OF_CONDUCT.md) before participating.

---
<h2>Our Team</h2>
<table>
<tr>
<td align="center">
<a href="https://github.com/Soham-Metha"><img src="https://avatars.githubusercontent.com/u/136834568?v=4" height="140px" width="140px" alt=""></a><br><sub><b>Soham-Metha</b><br><a href="https://www.linkedin.com/in/soham-metha-6692752b3/"><img src="https://github-production-user-asset-6210df.s3.amazonaws.com/73993775/278833250-adb040ea-e3ef-446e-bcd4-3e8d7d4c0176.png" width="45px" height="45px"></a></sub>
</td>
</tr>
</table>
<!--

---
<div align="center">
  <h2 style="font-size:3rem;">Our Contributors <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Red%20Heart.png" alt="Red Heart" width="40" height="40" /></h2>
  </div>
  <h3>Thanks to these amazing people who have contributed to the **virex** project:</h3>
<p align="center">
    <img src="https://api.vaunt.dev/v1/github/entities/Soham-Metha/repositories/virex/contributors?format=svg&limit=54" width="1000" />
</p> -->

[![Stargazers repo roster for @Soham-Metha/virex](https://reporoster.com/stars/dark/Soham-Metha/virex)](https://github.com/Soham-Metha/virex/stargazers)

[![Forkers repo roster for @Soham-Metha/virex](https://reporoster.com/forks/dark/Soham-Metha/virex)](https://github.com/Soham-Metha/virex/network/members)


<p style="font-family:var(--ff-philosopher);font-size:3rem;"><b> Show some <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Smilies/Red%20Heart.png" alt="Red Heart" width="40" height="40" /> by starring this awesome repository!
</p>
<!--
---
***🚀 Virex: Enabling Clean-Room Virtual Machines—One SASM Instruction at a Time! 🧬✨***
 **👨‍💻 Developed By**  **❤️Soham-Metha❤️**
[GitHub](https://github.com/Soham-Metha/) | [LinkedIn](https://www.linkedin.com/in/soham-metha-6692752b3/)
[🔝 Back to Top](#top)-->
