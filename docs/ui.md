### 🪟 Window Streams (UI Layout & Output Channels)

The UI system in VIREX is undergoing a refactor toward a more modular, plugin-based architecture. Each visual or I/O region in the interface is identified using a Window Stream ID (WindowID). These IDs represent distinct UI sections such as memory display, output console, or input handling.

The final stream (CREDITS) is currently used for displaying credits, but may be **repurposed** or expanded in the future.

!!! info ""

    Stream IDs are passed to internal and plugin-rendered window handlers to control layout and routing of output.

=== "UNDOCUMENTED"

    | ID | Name                  | Purpose                         |
    |----|-----------------------|---------------------------------|
    | 0  | [OUTPUT](../reference/missing.md)  | Standard output console         |
    | 1  | [INPUT](../reference/missing.md)   | Input area (if supported)       |
    | 2  | [DETAILS](../reference/missing.md) | Instruction or register details |
    | 3  | [MEMORY](../reference/missing.md)  | Visual memory dump              |
    | 4  | [PROGRAM](../reference/missing.md) | Current program or source view  |
    | 5  | [NAME](../reference/missing.md)    | Title / name bar                |
    | 6  | [CREDITS](../reference/missing.md) | Currently used for credits      |
