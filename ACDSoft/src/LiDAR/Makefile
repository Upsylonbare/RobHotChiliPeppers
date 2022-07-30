#
# ACDSoft - Makefile for a module (deal with cpp)
#

#
# Src organization
#
SRC = $(wildcard *.c)
SRC++ = $(wildcard *.cpp)
OBJ = $(SRC:.c=.o) $(SRC++:.cpp=.o)
DEP = $(SRC:.c=.d) $(SRC++:.cpp=.d)

#
# Makefile targets
#
CCFLAGS += -I.

# Compilation
all: $(OBJ)

%.o:%.c
	$(CC) -c $(CCFLAGS) $< -o $@  

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@  

# Cleaning.
clean:
	@rm -f $(OBJ) $(DEP)