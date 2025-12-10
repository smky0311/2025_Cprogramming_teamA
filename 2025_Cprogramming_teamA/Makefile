# ============================================
# Makefile for Library Management System
# ============================================
# This Makefile compiles the Library Management System
# using GCC with proper flags for debugging and warnings.
#
# Usage:
#   make        - Build the program
#   make clean  - Remove compiled files
#   make run    - Build and run the program
# ============================================

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Target executable name
TARGET = library_system

# Source files
SRCS = main.c user.c admin.c utils.c mine.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files (for dependency tracking)
HEADERS = book.h user.h common.h admin.h utils.h mine.h

# ============================================
# Build Rules
# ============================================

# Default target: build the executable
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up build files."

# Build and run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Show help information
help:
	@echo "Library Management System - Makefile Help"
	@echo "=========================================="
	@echo "Available targets:"
	@echo "  make        - Build the program"
	@echo "  make clean  - Remove compiled files"
	@echo "  make run    - Build and run the program"
	@echo "  make rebuild- Clean and rebuild"
	@echo "  make help   - Show this help message"
	@echo ""
	@echo "Source files: $(SRCS)"
	@echo "Output: $(TARGET)"

# Phony targets (not actual files)
.PHONY: all clean run rebuild help
