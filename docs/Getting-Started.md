---

hide:
  - toc

---

??? info "bash commands"

    ```bash linenums="1" hl_lines="1 5 8"
    # 1. CLONING
    git clone https://github.com/Soham-Metha/virex.git
    cd virex/

    # 2. BUILD (sudo)
    ./install.sh

    # 3. RUN VIREX (in the sample programs DIR)
    cd ./examples/SASM/
    virex
    ```

1. **Clone this repo**

2. **Build the project (requires `sudo`)**

3. **Run an example program**

??? question "UI doesn't render properly"
    If the **TUI doesn't render properly**, try adjusting your **terminal font size**.

    If that doesn't help, you can tweak layout values in **src/VM/vm_tui.c::CreateWindows()**.
    The constants used are defined as **percentages** of the screen dimensions.

    P.S. **kitty terminal** config, and font used, are available in `/tools`

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
