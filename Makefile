
#* NAMING FORMAT
#* G = GLOBAL, A = ASSEMBLER, C = COMPILER, M = MACHINE
#* I = INCLUDE, C = CODE
#* DIR = DIRECTORY

GIDIR := ./include/libs
CIDIR := ./include/OCC
AIDIR := ./include/SASM
MIDIR := ./include/VM

GCDIR := ./src/libs
CCDIR := ./src/OCC
ACDIR := ./src/SASM
MCDIR := ./src/VM

OMAIN := $(CCDIR)/O_main.c
SMAIN := $(ACDIR)/sasm_main.c
VMAIN := $(MCDIR)/virex_main.c
BUILD := ./build

OBUILD := $(BUILD)/occ
SBUILD := $(BUILD)/sasm
VBUILD := $(BUILD)/virex

CC	   := gcc
CFLAGS := -Wall -Wextra -Werror -Wfatal-errors -Wswitch-enum -pedantic -O3 -std=c2x
LIBS   := -lncursesw -I$(GIDIR) -I$(CIDIR) -I$(AIDIR) -I$(MIDIR)

G_HEAD := $(wildcard $(GIDIR)/*.h)
C_HEAD := $(wildcard $(CIDIR)/*.h)
A_HEAD := $(wildcard $(AIDIR)/*.h)
M_HEAD := $(wildcard $(MIDIR)/*.h)


G_CODE := $(wildcard $(GCDIR)/*.c)
C_CODE := $(wildcard $(CCDIR)/*.c)
A_CODE := $(wildcard $(ACDIR)/*.c)
M_CODE := $(wildcard $(MCDIR)/*.c)


C_CODE := $(filter-out $(OMAIN), $(C_CODE))
A_CODE := $(filter-out $(SMAIN), $(A_CODE))

.PHONY: clean occ sasm virex all

all		: 	virex
virex	: 	occ		sasm 	   $(VBUILD)

occ		: 	$(OBUILD)
sasm	: 	$(SBUILD)

$(OBUILD):	$(OMAIN) $(G_CODE) $(C_CODE) | $(BUILD)
		@$(CC) $^    $(CFLAGS) $(LIBS) -o $@
		@echo  "\n					COMPILER MADE SUCCESSFULLY	\n"

$(SBUILD): 	$(SMAIN) $(G_CODE) $(A_CODE) | $(BUILD)
		@$(CC) $^    $(CFLAGS) $(LIBS) -o $@
		@echo  "\n	  				SASM MADE SUCCESSFULLY		\n"

$(VBUILD): 	$(VMAIN) $(G_CODE) $(M_CODE) $(A_CODE) | $(BUILD)
	  	@$(CC) $^    $(CFLAGS) $(LIBS) -o $@
		@echo  "\n	  				VM MADE SUCCESSFULLY		\n"

$(BUILD):
		mkdir -p $@

clean: | $(BUILD)
		@rm -f $(BUILD)/*
		@echo  "\n  CLEANED ALL OBJECT FILES AND EXECUTABLES	\n"
