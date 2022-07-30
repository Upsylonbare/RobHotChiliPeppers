#
# Makefile for a test module
# 

#
# SRC Organization
#
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Gcov informations
GCDA = $(SRC:.c=.gcda)
GCNO = $(SRC:.c=.gcno)

# Include from the level of the package
CCFLAGS += -I.. -I../../$(SRCDIR)

#
# Makefile targets
#

# Compilation.
tests: $(OBJ)

%.o:%.c
	$(CC) -c $(CCFLAGS) $< -o $@
	

.PHONY: clean

#Cleaning.
clean:
	@rm -f $(OBJ) $(DEP) $(GCDA) $(GCNO)