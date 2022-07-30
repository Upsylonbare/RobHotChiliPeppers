#
# ACDSoft - Makefile principal.
# 
# @author Thibault Malary, Jean-Théophane Deschard, Clément Le Goffic
#



# Cmocka path
export CMOCKA = $(realpath libs/cmocka-x86_64/)

#
# Source Organization
#
export SRCDIR = src
export TESTDIR = test
export LIBDIR = libs
export SDK = $(LIBDIR)/lidar-x86_64/sdk
export BINDIR = bin
export CHECK_DIR = report
export DOCDIR = doc

ALLDIR = $(SRCDIR) $(TESTDIR) $(SDK)

#
# Tool definition
#

# Check make option

ifeq ($(TARGET), mp1)
# for STM32MP157C-DK2.
# do nothing as CC and CCX are setup from environment variables.
else
# On other targets, use the default compiler.
export CC = gcc
export CXX = g++
export CXXFLAGS = -Wall
endif

ifeq ($(DEBUG), true)
# Debug mode
export CCFLAGS += -O0 
export CCFLAGS += -g -DDEBUG
export LDFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
else
# Prod mode
export CCFLAGS += -O3 
export CCFLAGS += -DNDEBUG
endif

# CC flags
export CCFLAGS += -MMD -MP
export CCFLAGS += -D_BSD_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_DEFAULT_SOURCE -D_GNU_SOURCE -D_POSIX_C_SOURCE=199309L -D_REENTRANT -g `pkg-config --cflags gtk+-3.0`
export CCFLAGS += -std=c99 -Wall
export LDFLAGS += -lrt -pthread `pkg-config --libs gtk+-3.0` -lstdc++ -lm

#
# Binary definition
#
export PROG = $(BINDIR)/ACDSoft
export TEST = $(BINDIR)/ACDSoft_test

#
# Makefile's targets
#

# recursive compilation.
all: $(SDK) $(SRCDIR)
	@echo "\033[31mWarnings come from LiDAR's SDK not from us :) (will be solved in the future...)\033[39m"

$(SRCDIR):
	@$(MAKE) $(MAKECMDGOALS) -C $@

$(SDK):
	@$(MAKE) $(MAKECMDGOALS) -C $@

$(TESTDIR):
	@$(MAKE) $(MAKECMDGOALS) -C $@

tests: $(TESTDIR)

test_report:
	@cd $(TESTDIR)
	@$(MAKE) $@

clean: $(SRCDIR) $(SDK) $(TESTDIR)
	@rm -f $(PROG) $(TEST)
	@rm -rf $(DOCDIR)/html
	@rm -f $(CHECK_DIR)/*

check:
	@[ -d $(CHECK_DIR) ] || mkdir -p $(CHECK_DIR)
	@cppcheck --enable=all --xml --xml-version=2 --suppress=missingInclude ./ 2>$(CHECK_DIR)/report.xml
	@cppcheck-htmlreport --source-dir=./ , --file=$(CHECK_DIR)/report.xml , --report-dir=$(CHECK_DIR) , --title="ACDSoft"

docs:
	@doxygen $(DOCDIR)/Doxyfile

help:
	@cat doc/acdsoft-header.txt
	@echo "Usage: make [target] [options]"
	@echo "Target:"
	@echo "  all: compile LiDAR sdk and sources, generate binary bin/ACDSoft"
	@echo "  tests: compile tests, generate binary bin/ACDSoft_test"
	@echo "  test_report: generate a test report \033[31mYou must launch test binary before and install gcovr (pip install gcovr)\033[39m"
	@echo "  clean: clean everything"
	@echo "  check: check code with cppcheck"
	@echo "  docs: generate documentation with doxygen"
	@echo "Options"
	@echo "  DEBUG=true: compile in debug mode"
	@echo "  TARGET=mp1: compile for STM32MP157C-DK2 \033[31mYou must source the sdk file before using this option\033[39m"

.PHONY: clean $(SRCDIR) $(SDK) $(TESTDIR) tests test_report check docs src