🧩 Parsing Structure & Symbol Representation

The assembler follows a layered parsing pipeline:

0. Source files are split into lines (LineType)

1. Each line is resolved into a statement (StmtType)

2. Each statement contains expressions (ExprType)

3. Expressions are made of tokens (TokenType)

4. Some expressions are bindings to values or labels (BindingType)

Bound symbols like labels and constants are differentiated using BindingType.

=== "UNDOCUMENTED"

    === "Line Types"

        | Value | Name                        |
        |-------|-----------------------------|
        | 0     | [LINE_INSTRUCTION](../reference/missing.md) |
        | 1     | [LINE_LABEL](../reference/missing.md)       |
        | 2     | [LINE_DIRECTIVE](../reference/missing.md)   |


    === "Statement Types"

        | Value | Name              |
        |-------|-------------------|
        | 0     | [STMT_INST](../reference/missing.md)     |
        | 1     | [STMT_LABEL](../reference/missing.md)    |
        | 2     | [STMT_CONST](../reference/missing.md)    |
        | 3     | [STMT_INCLUDE](../reference/missing.md)  |
        | 4     | [STMT_ENTRY](../reference/missing.md)    |
        | 5     | [STMT_BLOCK](../reference/missing.md)    |
        | 6     | [STMT_SCOPE](../reference/missing.md)    |

    === "Expression Types"

        | Value | Name                  |
        |-------|-----------------------|
        | 0     | [EXPR_BINDING](../reference/missing.md)     |
        | 1     | [EXPR_LIT_INT](../reference/missing.md)     |
        | 2     | [EXPR_LIT_FLOAT](../reference/missing.md)   |
        | 3     | [EXPR_LIT_CHAR](../reference/missing.md)    |
        | 4     | [EXPR_LIT_STR](../reference/missing.md)     |
        | 5     | [EXPR_FUNCALL](../reference/missing.md)     |
        | 6     | [EXPR_REG](../reference/missing.md)         |

    === "Token Types"

        | Value | Name                         |
        |-------|------------------------------|
        | 0     | [TOKEN_TYPE_STR](../reference/missing.md)       |
        | 1     | [TOKEN_TYPE_CHAR](../reference/missing.md)      |
        | 2     | [TOKEN_TYPE_NUMBER](../reference/missing.md)    |
        | 3     | [TOKEN_TYPE_NAME](../reference/missing.md)      |
        | 4     | [TOKEN_TYPE_OPEN_PAREN](../reference/missing.md)   |
        | 5     | [TOKEN_TYPE_CLOSING_PAREN](../reference/missing.md)|
        | 6     | [TOKEN_TYPE_COMMA](../reference/missing.md)     |
        | 7     | [TOKEN_TYPE_REGISTER](../reference/missing.md)  |

    === "Binding Types"

        | Value | Name                        |
        |-------|-----------------------------|
        | 0     | [BIND_TYPE_FLOAT](../reference/missing.md)     |
        | 1     | [BIND_TYPE_UINT](../reference/missing.md)      |
        | 2     | [BIND_TYPE_MEM_ADDR](../reference/missing.md)  |
        | 3     | [BIND_TYPE_INST_ADDR](../reference/missing.md) |
