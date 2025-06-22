
#* NAMING FORMAT
#* I = INCLUDE, C = CODE
#* G = GLOBAL, A = ASSEMBLER, C = COMPILER, M = MACHINE
#* DIR = DIRECTORY

GIDIR = ./include/libs
CIDIR = ./include/OCC
AIDIR = ./include/SASM
MIDIR = ./include/VM

GCDIR = ./src/libs
CCDIR = ./src/OCC
ACDIR = ./src/SASM
MCDIR = ./src/VM

OCC_MAIN   = $(CCDIR)/O_main.c
SASM_MAIN  = $(ACDIR)/sasm_main.c
VIREX_MAIN = $(MCDIR)/virex_main.c

CC	   = gcc
CFLAGS = -Wall -Wextra -Werror -Wfatal-errors -Wswitch-enum -pedantic -O3 -std=c2x
LIBS   = -lncursesw -I$(GIDIR) -I$(CIDIR) -I$(AIDIR) -I$(MIDIR)


_G_HEAD  = 		univ_defs.h		 	 	univ_errors.h		 	univ_fileops.h			univ_strings.h
_G_HEAD +=	 	univ_hashmap.h			univ_malloc.h
G_HEAD   = 		$(patsubst %, 			$(GIDIR)/%,				$(_G_HEAD))

_G_CODE  = 		univ_defs.c				univ_errors.c			univ_fileops.c			univ_strings.c
_G_CODE +=		univ_hashmap.c			univ_malloc.c
G_CODE   = 		$(patsubst %, 			$(GCDIR)/%,				$(_G_CODE))


_C_HEAD  =		O_lexer.h				O_parser.h				O_parse_tree.h			O_inter_code_optimizer.h
_C_HEAD +=		O_inter_codegen.h 		O_debug_help.h			O_symbol_table.h		O_token_types.h
C_HEAD   =		$(patsubst %, 			$(CIDIR)/%,				$(_C_HEAD))

_C_CODE  = 		O_lexer.c				O_parser.c				O_parse_tree.c			O_inter_code_optimizer.c
_C_CODE +=		O_inter_codegen.c		O_debug_help.c	  		O_symbol_table.c
C_CODE   = 		$(patsubst %, 			$(CCDIR)/%,				$(_C_CODE))


_A_HEAD  = 		sasm_assembler.h		sasm_instructions.c
A_HEAD   = 		$(patsubst %, 			$(AIDIR)/%,				$(_A_HEAD))

_A_CODE  = 		sasm_assembler.c		sasm_instructions.c		sasm_binding.c	  		sasm_ast.c
_A_CODE +=	  sasm_tokenizer.c			sasm_expressions.c		sasm_lexer.c			sasm_parser.c		
A_CODE   = 		$(patsubst %, 			$(ACDIR)/%,				$(_A_CODE))


_M_HEAD  = 		virex_assembler.h		virex_vmcalls.h			virex_tui.h	 			virex.h
M_HEAD   = 		$(patsubst %, 			$(MIDIR)/%,				$(_M_HEAD))

_M_CODE  =		virex_assembler.c		virex_vmcalls.c			virex_tui.c				virex.c
M_CODE   =		$(patsubst %, 			$(MCDIR)/%,				$(_M_CODE))

.PHONY: clean

occ:	$(OCC_MAIN)  $(G_CODE) $(C_CODE) 
		@$(CC) -o ./build/$@ $^   $(CFLAGS) $(LIBS)
		@echo  "\n					COMPILER MADE SUCCESSFULLY	\n"

sasm: 	$(SASM_MAIN) $(G_CODE) $(A_CODE)
		@$(CC) -o ./build/$@ $^   $(CFLAGS) $(LIBS)
		@echo  "\n	  					SASM MADE SUCCESSFULLY	\n"

virex: 	$(VIREX_MAIN) $(G_CODE) $(M_CODE) $(A_CODE)
		@make occ
		@make sasm
	  	@$(CC) -o ./build/$@ $^   $(CFLAGS) $(LIBS)
		@echo  "\n	  					VM MADE SUCCESSFULLY	\n"

clean:
		@rm -f ./build/*
		@echo  "\n  CLEANED ALL OBJECT FILES AND EXECUTABLES	\n"
