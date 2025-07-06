#* G = GLOBAL LIBS, C = COMPILER, A = ASSEMBLER, M = MACHINE
BUILDS := ./build

C_EXEC := $(BUILDS)/orin
A_EXEC := $(BUILDS)/sasm
M_EXEC := $(BUILDS)/virex

_G_DIR := ./src/libs
_C_DIR := ./src/OCC
_A_DIR := ./src/SASM
_M_DIR := ./src/VM

C_MAIN := $(_C_DIR)/O_main.c
A_MAIN := $(_A_DIR)/sasm_main.c
M_MAIN := $(_M_DIR)/virex_main.c

G_CODE := $(wildcard   $(_G_DIR)/*.c)
C_CODE := $(filter-out $(C_MAIN), 	$(wildcard $(_C_DIR)/*.c) )
A_CODE := $(filter-out $(A_MAIN), 	$(wildcard $(_A_DIR)/*.c) )
M_CODE := $(filter-out $(M_MAIN), 	$(wildcard $(_M_DIR)/*.c) )

CC	   := gcc
CFLAGS := -Wall -Wextra -Werror -Wfatal-errors -Wswitch-enum -pedantic -O3 -std=c2x
LIBS   := -lncursesw $(addprefix -I, $(wildcard ./include/*/))

.PHONY: clean occ sasm virex all

all 	: 	$(C_EXEC)	$(A_EXEC) 	$(M_EXEC)
orin 	: 	$(C_EXEC)
sasm	: 	$(A_EXEC)
virex	: 	$(C_EXEC)	$(A_EXEC) 	$(M_EXEC)

define BUILD_RULE
$1: $2 $(G_CODE) | $(BUILDS)
	@$(CC) $$^ $(CFLAGS) $(LIBS) -o $$@
	@printf "\e[32m		[ BUILD COMPLETED ]\t: [ $$@ ] \e[0m\n\n"
endef

$(eval $(call BUILD_RULE, $(C_EXEC),  $(C_MAIN) $(C_CODE)))
$(eval $(call BUILD_RULE, $(A_EXEC),  $(A_MAIN) $(A_CODE)))
$(eval $(call BUILD_RULE, $(M_EXEC),  $(M_MAIN) $(M_CODE) $(A_CODE)))

$(BUILDS):
	@mkdir -p $@

clean: | $(BUILDS)
	@rm -f $(BUILDS)/*
	@printf  "\n\e[36m  CLEANED ALL OBJECT FILES AND EXECUTABLES	\e[0m\n\n"

<<<<<<< HEAD
html: clean-html
	@mkdocs build -f mkdocs.yml

clean-html:
=======
html: clean-docs
	@mkdocs build -f mkdocs.yml

clean-docs:
>>>>>>> 27e174fdf8069df9b03e30c5d69c587551eff4bf
	@rm -rfv html