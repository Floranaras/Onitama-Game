# Makefile for Onitama Game
# Usage: make, make run, make clean, make help

# ========== CONFIGURATION ==========
CC = gcc
CFLAGS = -Wall -std=c99 -I./include
LDFLAGS = 

# ========== DIRECTORIES ==========
SRCDIR = src
INCDIR = include
OBJDIR = obj
DATADIR = data

# ========== FILES ==========
TARGET = $(OBJDIR)/onitama
SOURCES = $(wildcard $(SRCDIR)/*.c) main.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
HEADERS = $(wildcard $(INCDIR)/*.h)

# ========== COLORS FOR OUTPUT ==========
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m # No Color

# ========== DEFAULT TARGET ==========
all: $(TARGET)
	@echo "$(GREEN)Build complete: $(TARGET)$(NC)"

# ========== BUILD EXECUTABLE ==========
$(TARGET): $(OBJDIR) $(OBJECTS)
	@echo "$(YELLOW)Linking $(TARGET)...$(NC)"
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# ========== CREATE OBJECT DIRECTORY ==========
$(OBJDIR):
	@echo "$(YELLOW)Creating obj directory...$(NC)"
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)

# ========== COMPILE SOURCE FILES ==========
$(OBJDIR)/%.o: %.c $(HEADERS)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# ========== RUN THE GAME ==========
run: $(TARGET)
	@echo "$(GREEN)Starting Onitama...$(NC)"
	@echo "$(YELLOW)===============================$(NC)"
	$(TARGET)

# ========== CLEAN BUILD ARTIFACTS ==========
clean:
	@echo "$(RED)Cleaning build artifacts...$(NC)"
	rm -rf $(OBJDIR)
	@echo "$(GREEN)Clean complete$(NC)"

# ========== FORCE REBUILD ==========
rebuild: clean all

# ========== DEBUG BUILD ==========
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "$(GREEN)Debug build complete$(NC)"

# ========== RELEASE BUILD ==========
release: CFLAGS += -O2
release: clean $(TARGET)
	@echo "$(GREEN)Release build complete$(NC)"

# ========== INSTALL (copy to system directory) ==========
install: $(TARGET)
	@echo "$(YELLOW)Installing onitama...$(NC)"
	sudo cp $(TARGET) /usr/local/bin/onitama
	@echo "$(GREEN)Installed to /usr/local/bin/$(NC)"

# ========== UNINSTALL ==========
uninstall:
	@echo "$(RED)Uninstalling onitama...$(NC)"
	sudo rm -f /usr/local/bin/onitama
	@echo "$(GREEN)Uninstalled$(NC)"

# ========== SHOW PROJECT INFO ==========
info:
	@echo "$(YELLOW)Project Information:$(NC)"
	@echo "  Target:     $(TARGET)"
	@echo "  Sources:    $(words $(SOURCES)) files"
	@echo "  Headers:    $(words $(HEADERS)) files" 
	@echo "  Compiler:   $(CC)"
	@echo "  Flags:      $(CFLAGS)"
	@echo "  Build dir:  $(OBJDIR)/"

# ========== CHECK FOR REQUIRED FILES ==========
check:
	@echo "$(YELLOW)Checking project files...$(NC)"
	@test -d $(SRCDIR) || (echo "$(RED)Missing $(SRCDIR)/ directory$(NC)" && exit 1)
	@test -d $(INCDIR) || (echo "$(RED)Missing $(INCDIR)/ directory$(NC)" && exit 1)
	@test -d $(DATADIR) || (echo "$(RED)Missing $(DATADIR)/ directory$(NC)" && exit 1)
	@test -f main.c || (echo "$(RED)Missing main.c$(NC)" && exit 1)
	@test -f $(DATADIR)/movecards.txt || (echo "$(RED)Missing $(DATADIR)/movecards.txt$(NC)" && exit 1)
	@echo "$(GREEN)All required files present$(NC)"

# ========== COUNT LINES OF CODE ==========
count:
	@echo "$(YELLOW)Lines of code:$(NC)"
	@wc -l $(SOURCES) $(HEADERS) | tail -1

# ========== HELP ==========
help:
	@echo "$(YELLOW)Onitama Makefile Help$(NC)"
	@echo ""
	@echo "$(GREEN)Main Targets:$(NC)"
	@echo "  make         - Build the project (default)"
	@echo "  make run     - Build and run the game"
	@echo "  make clean   - Remove all build artifacts"
	@echo ""
	@echo "$(GREEN)Build Options:$(NC)"
	@echo "  make debug   - Build with debug symbols"
	@echo "  make release - Build optimized release version"
	@echo "  make rebuild - Clean and build"
	@echo ""
	@echo "$(GREEN)Utility Targets:$(NC)"
	@echo "  make check   - Verify all required files exist"
	@echo "  make info    - Show project information"
	@echo "  make count   - Count lines of code"
	@echo "  make help    - Show this help message"
	@echo ""
	@echo "$(GREEN)Installation:$(NC)"
	@echo "  make install   - Install to system (requires sudo)"
	@echo "  make uninstall - Remove from system (requires sudo)"

# ========== TEST BUILD ==========
test: | $(OBJDIR) $(OBJDIR)/testmain
	@echo "$(GREEN)Running test executable...$(NC)"
	./$(OBJDIR)/testmain

$(OBJDIR)/testmain: testing/testmain.c $(wildcard $(SRCDIR)/*.c) $(HEADERS)
	@echo "$(YELLOW)Building test executable...$(NC)"
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) testing/testmain.c $(SRCDIR)/*.c -o $(OBJDIR)/testmain
# ========== PHONY TARGETS ==========
.PHONY: all run clean rebuild debug release install uninstall info check count help

# ========== DEPENDENCY TRACKING ==========
-include $(OBJECTS:.o=.d)
