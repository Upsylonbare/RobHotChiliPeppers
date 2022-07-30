#
# ACDSoft - SRC Makefile
#

#
# SRC Organization
#

# Project's packages
PACKAGES = Folder NetworkC Converter Geographer LiDAR UI Merger
# Lidar's static library
STATLIB = ../libs/lidar-x86_64/output/librplidar_sdk.a


MAIN = starter.c

DEP = $(MAIN:.c=.d)

# binary name
EXEC = ../$(PROG)

# Linker flags
LDFLAGS += -lrt -pthread `pkg-config --libs gtk+-3.0` -lstdc++ -lm 

# Object files
SRC = $(wildcard */*.c)	
SRC += $(wildcard */*/*.c)
SRC++ = $(wildcard */*.cpp)
OBJ = $(SRC:.c=.o) $(SRC++:.cpp=.o)

#
# Makefile's rules.
#

# Compilation.
all: $(PACKAGES) $(EXEC)

$(PACKAGES):
	@$(MAKE) $(MAKECMDGOALS) -C $@

$(EXEC): $(OBJ) $(MAIN)
	$(CC) $(CCFLAGS) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS) $(STATLIB)

.PHONY: all clean $(PACKAGES)

clean: $(PACKAGES)
	@rm -f $(DEP)

