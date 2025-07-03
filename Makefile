# Makefile for Onitama Game - Unified Build System
# Supports: main game, test suite, cross-platform compilation
# Usage: make, make run, make test, make clean, make help

# ========== CONFIGURATION ==========
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
LDFLAGS = 

# ========== DIRECTORIES ==========
SRCDIR = src
INCDIR = include
OBJDIR = obj
DATADIR = data
TESTDIR = testing

# ========== TARGET DETECTION ==========
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    # Check if we're in a Unix-like environment on Windows (Git Bash, WSL, MSYS2)
    ifneq ($(shell echo $0 | grep -E "(bash|sh)"),)
        UNIX_ON_WINDOWS := 1
        MKDIR_CMD := mkdir -p
        RM_CMD := rm -rf
        PATH_SEP := /
    else
        UNIX_ON_WINDOWS := 0
        MKDIR_CMD := mkdir
        RM_CMD := rmdir /s /q
        PATH_SEP := \\
    endif
else
    DETECTED_OS := $(shell uname -s)
    UNIX_ON_WINDOWS := 0
    EXE_EXT := 
    MKDIR_CMD := mkdir -p
    RM_CMD := rm -rf
    PATH_SEP := /
endif

# ========== FILES ==========
MAIN_TARGET = $(OBJDIR)/onitama$(EXE_EXT)
TEST_TARGET = $(OBJDIR)/test_onitama$(EXE_EXT)

MAIN_SOURCES = main.c $(wildcard $(SRCDIR)/*.c)
TEST_SOURCES = $(TESTDIR)/testscript.c $(wildcard $(SRCDIR)/*.c)

MAIN_OBJECTS = $(MAIN_SOURCES:%.c=$(OBJDIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.c=$(OBJDIR)/%.o)

HEADERS = $(wildcard $(INCDIR)/*.h)

# ========== COLORS FOR OUTPUT ==========
# Detect if colors are supported
ifeq ($(DETECTED_OS),Windows)
    ifeq ($(UNIX_ON_WINDOWS),1)
        # Unix-like environment on Windows (Git Bash, WSL) - colors should work
        GREEN = \033[0;32m
        YELLOW = \033[1;33m
        RED = \033[0;31m
        BLUE = \033[0;34m
        PURPLE = \033[0;35m
        CYAN = \033[0;36m
        NC = \033[0m
    else
        # Pure Windows CMD - no colors
        GREEN = 
        YELLOW = 
        RED = 
        BLUE = 
        PURPLE = 
        CYAN = 
        NC = 
    endif
else
    # Unix systems - colors supported
    GREEN = \033[0;32m
    YELLOW = \033[1;33m
    RED = \033[0;31m
    BLUE = \033[0;34m
    PURPLE = \033[0;35m
    CYAN = \033[0;36m
    NC = \033[0m
endif

# ========== DEFAULT TARGET ==========
all: $(MAIN_TARGET)
	@echo "$(GREEN)✓ Build complete: $(MAIN_TARGET)$(NC)"
	@echo "$(CYAN)  Run with: make run$(NC)"
	@echo "$(CYAN)  Test with: make test$(NC)"

# ========== BUILD MAIN GAME ==========
$(MAIN_TARGET): $(OBJDIR) $(MAIN_OBJECTS)
	@echo "$(YELLOW)  Linking main game...$(NC)"
	$(CC) $(filter-out $(OBJDIR)/$(TESTDIR)/%.o,$(MAIN_OBJECTS)) $(LDFLAGS) -o $(MAIN_TARGET)

# ========== BUILD TEST SUITE ==========
$(TEST_TARGET): $(OBJDIR) $(TEST_OBJECTS)
	@echo "$(YELLOW)  Linking test suite...$(NC)"
	$(CC) $(filter-out $(OBJDIR)/main.o,$(TEST_OBJECTS)) $(LDFLAGS) -o $(TEST_TARGET)

# ========== CREATE DIRECTORIES ==========
$(OBJDIR):
	@echo "$(YELLOW)  Creating build directories...$(NC)"
ifeq ($(DETECTED_OS),Windows)
    ifeq ($(UNIX_ON_WINDOWS),1)
	@$(MKDIR_CMD) $(OBJDIR)
	@$(MKDIR_CMD) $(OBJDIR)/$(SRCDIR)
	@$(MKDIR_CMD) $(OBJDIR)/$(TESTDIR)
    else
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"
	@if not exist "$(OBJDIR)\$(SRCDIR)" mkdir "$(OBJDIR)\$(SRCDIR)"
	@if not exist "$(OBJDIR)\$(TESTDIR)" mkdir "$(OBJDIR)\$(TESTDIR)"
    endif
else
	@$(MKDIR_CMD) $(OBJDIR)
	@$(MKDIR_CMD) $(OBJDIR)/$(SRCDIR)
	@$(MKDIR_CMD) $(OBJDIR)/$(TESTDIR)
endif

# ========== COMPILE SOURCE FILES ==========
$(OBJDIR)/%.o: %.c $(HEADERS)
	@echo "$(YELLOW)   Compiling $<...$(NC)"
	@$(MKDIR_CMD) $(dir $@) 2>/dev/null || true
	$(CC) $(CFLAGS) -c $< -o $@

# ========== RUN MAIN GAME ==========
run: $(MAIN_TARGET)
	@echo "$(GREEN)  Starting Onitama Game...$(NC)"
	@echo "$(PURPLE)===============================$(NC)"
	@$(MAIN_TARGET)

# ========== RUN TEST SUITE ==========
test: $(TEST_TARGET)
	@echo "$(GREEN)  Running Test Suite...$(NC)"
	@echo "$(PURPLE)===============================$(NC)"
	@$(TEST_TARGET)

# ========== BUILD AND RUN TESTS ==========
test-run: test
	@echo "$(CYAN)Tests completed!$(NC)"

# ========== QUICK TEST (ONE COMMAND) ==========
quick-test:
	@echo "$(YELLOW)  Quick test compilation and run...$(NC)"
	$(CC) $(CFLAGS) $(TESTDIR)/testscript.c $(wildcard $(SRCDIR)/*.c) -o $(TESTDIR)/quick_test$(EXE_EXT)
	@$(TESTDIR)/quick_test$(EXE_EXT)
	@$(RM_CMD) $(TESTDIR)/quick_test$(EXE_EXT) 2>/dev/null || true

# ========== CLEAN BUILD ARTIFACTS ==========
clean:
	@echo "$(RED)🧹 Cleaning build artifacts...$(NC)"
ifeq ($(DETECTED_OS),Windows)
    ifeq ($(UNIX_ON_WINDOWS),1)
	@$(RM_CMD) $(OBJDIR) 2>/dev/null || true
	@$(RM_CMD) $(TESTDIR)/quick_test$(EXE_EXT) 2>/dev/null || true
    else
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(TESTDIR)\quick_test$(EXE_EXT)" del "$(TESTDIR)\quick_test$(EXE_EXT)"
    endif
else
	@$(RM_CMD) $(OBJDIR) 2>/dev/null || true
	@$(RM_CMD) $(TESTDIR)/quick_test 2>/dev/null || true
endif
	@echo "$(GREEN)✓ Clean complete$(NC)"

# ========== BUILD BOTH TARGETS ==========
both: $(MAIN_TARGET) $(TEST_TARGET)
	@echo "$(GREEN)✓ Both main game and test suite built successfully!$(NC)"

# ========== FORCE REBUILD ==========
rebuild: clean all

# ========== DEBUG BUILD ==========
debug: CFLAGS += -g -DDEBUG -O0
debug: clean $(MAIN_TARGET)
	@echo "$(GREEN)  Debug build complete$(NC)"

# ========== RELEASE BUILD ==========
release: CFLAGS += -O2 -DNDEBUG
release: clean $(MAIN_TARGET)
	@echo "$(GREEN)  Release build complete$(NC)"

# ========== PLATFORM INFO ==========
platform-info:
	@echo "$(BLUE)   Platform Information:$(NC)"
	@echo "  Detected OS: $(DETECTED_OS)"
ifeq ($(DETECTED_OS),Windows)
	@echo "  Unix-like Environment: $(UNIX_ON_WINDOWS)"
endif
	@echo "  Executable Extension: $(EXE_EXT)"
	@echo "  Compiler: $(CC)"
	@echo "  Flags: $(CFLAGS)"

# ========== PROJECT INFO ==========
info: platform-info
	@echo "$(BLUE)📋 Project Information:$(NC)"
	@echo "  Main Target: $(MAIN_TARGET)"
	@echo "  Test Target: $(TEST_TARGET)"
	@echo "  Main Sources: $(words $(MAIN_SOURCES)) files"
	@echo "  Headers: $(words $(HEADERS)) files"
	@echo "  Build Directory: $(OBJDIR)/"

# ========== CHECK REQUIREMENTS ==========
check:
	@echo "$(YELLOW)🔍 Checking project files...$(NC)"
	@test -d $(SRCDIR) || (echo "$(RED)  Missing $(SRCDIR)/ directory$(NC)" && exit 1)
	@test -d $(INCDIR) || (echo "$(RED)  Missing $(INCDIR)/ directory$(NC)" && exit 1)
	@test -d $(DATADIR) || (echo "$(RED)  Missing $(DATADIR)/ directory$(NC)" && exit 1)
	@test -f main.c || (echo "$(RED)  Missing main.c$(NC)" && exit 1)
	@test -f $(DATADIR)/movecards.txt || (echo "$(RED)  Missing $(DATADIR)/movecards.txt$(NC)" && exit 1)
	@if [ -f $(TESTDIR)/testscript.c ]; then \
		echo "$(GREEN)✓ Test script found$(NC)"; \
	else \
		echo "$(YELLOW)   Test script not found at $(TESTDIR)/testscript.c$(NC)"; \
	fi
	@echo "$(GREEN)✓ All core files present$(NC)"

# ========== COUNT LINES OF CODE ==========
count:
	@echo "$(BLUE)  Lines of code:$(NC)"
	@wc -l $(MAIN_SOURCES) $(HEADERS) | tail -1 || echo "wc command not available"

# ========== SETUP PROJECT ==========
setup:
	@echo "$(YELLOW)  Setting up project directories...$(NC)"
ifeq ($(DETECTED_OS),Windows)
	@if not exist "$(SRCDIR)" mkdir "$(SRCDIR)"
	@if not exist "$(INCDIR)" mkdir "$(INCDIR)"
	@if not exist "$(DATADIR)" mkdir "$(DATADIR)"
	@if not exist "$(TESTDIR)" mkdir "$(TESTDIR)"
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"
else
	@$(MKDIR_CMD) $(SRCDIR) 2>/dev/null || true
	@$(MKDIR_CMD) $(INCDIR) 2>/dev/null || true
	@$(MKDIR_CMD) $(DATADIR) 2>/dev/null || true
	@$(MKDIR_CMD) $(TESTDIR) 2>/dev/null || true
	@$(MKDIR_CMD) $(OBJDIR) 2>/dev/null || true
endif
	@echo "$(GREEN)✓ Project setup complete$(NC)"

# ========== HELP ==========
help:
	@echo "$(BLUE)  Onitama Unified Build System$(NC)"
	@echo ""
	@echo "$(GREEN)  Main Targets:$(NC)"
	@echo "  make           - Build the main game (default)"
	@echo "  make run       - Build and run the game"
	@echo "  make clean     - Remove all build artifacts"
	@echo ""
	@echo "$(GREEN)  Testing:$(NC)"
	@echo "  make test      - Build and run test suite"
	@echo "  make quick-test - Compile and run tests in one step"
	@echo "  make both      - Build both game and tests"
	@echo ""
	@echo "$(GREEN)  Build Options:$(NC)"
	@echo "  make debug     - Build with debug symbols (-g -DDEBUG)"
	@echo "  make release   - Build optimized release (-O2)"
	@echo "  make rebuild   - Clean and build from scratch"
	@echo ""
	@echo "$(GREEN)  Utilities:$(NC)"
	@echo "  make check     - Verify all required files exist"
	@echo "  make info      - Show project and platform info"
	@echo "  make count     - Count lines of code"
	@echo "  make setup     - Create project directory structure"
	@echo "  make help      - Show this help message"
	@echo ""
	@echo "$(CYAN) Quick Start:$(NC)"
	@echo "  1. make check  - Verify setup"
	@echo "  2. make run    - Play the game"
	@echo "  3. make test   - Run all tests"
	@echo ""
	@echo "$(PURPLE) Cross-platform support: Windows, Linux, macOS$(NC)"

# ========== INSTALL/UNINSTALL (Unix only) ==========
ifneq ($(DETECTED_OS),Windows)
install: $(MAIN_TARGET)
	@echo "$(YELLOW) Installing onitama...$(NC)"
	sudo cp $(MAIN_TARGET) /usr/local/bin/onitama
	@echo "$(GREEN)✓ Installed to /usr/local/bin/$(NC)"

uninstall:
	@echo "$(RED)Uninstalling onitama...$(NC)"
	sudo rm -f /usr/local/bin/onitama
	@echo "$(GREEN)✓ Uninstalled$(NC)"
endif

# ========== DEPENDENCY TRACKING ==========
-include $(MAIN_OBJECTS:.o=.d)
-include $(TEST_OBJECTS:.o=.d)

# ========== PHONY TARGETS ==========
.PHONY: all run test test-run quick-test clean both rebuild debug release \
        platform-info info check count setup help install uninstall
