#
# ACDSoft - Makefile for a module
#


#
# Src organization
#
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Handle inclusion from the level of the package

#
# Makefile targets
#

# Compilation
all: $(OBJ)

%.o:%.c
	$(CC) -c $(CCFLAGS) $< -o $@
	
# Cleaning.
.PHONY: all clean

clean:
	@rm -f $(OBJ) $(DEP)