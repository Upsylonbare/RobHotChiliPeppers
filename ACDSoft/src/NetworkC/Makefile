#
# ACDSoft - Hierarchical Makefile for comm modules
#

# Module's packages
PACKAGES = Coder Dispatcher Postman Proxy

#
# Source organization
#
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Handle inclusion from the level of the package


#
# Makefile's targets
#

# Compilation
all: $(OBJ) $(PACKAGES)

%.o:%.c
	$(CC) -c $(CCFLAGS) $< -o $@

clean: $(PACKAGES)
	@rm -f $(OBJ) $(DEP)

$(PACKAGES):
	@$(MAKE) $(MAKECMDGOALS) -C $@

.PHONY: all clean $(PACKAGES)
