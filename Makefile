# Made by Serhij Čepil
# FIT VUT Student
# https://github.com/sipxi
# 09/10/2024

# The code is based on VUT FIT C Practicals


# Compiler and flags
CC 			= gcc #! CHANGE BASED ON YOUR COMPLIER
CFLAGS 		= -std=c11 -Wall -Wextra

# Executable names
EXEC        = tnine 
TEST_EXEC   = test_main

# Source files
MAIN_SRC    = src/tnine.c
TEST_SRC    = tests/test_module.c

# Targets
.PHONY: all run test clean

# Default target to build both the main and test executables
all: $(EXEC) $(TEST_EXEC)
	
# Build the main executable
$(EXEC): $(MAIN_SRC) 
	$(CC) $(CFLAGS) -o $@ $^

# Build the test executable
$(TEST_EXEC): $(MAIN_SRC) $(TEST_SRC) 
	$(CC) $(CFLAGS) -DTEST_BUILD=1 -o $@ $^

# Run the main program
run: $(EXEC)
	@echo "Running main..."

	./$(EXEC)

# Run all unit tests
test: $(TEST_EXEC)
	./$(TEST_EXEC) 

# Clean up compiled files
clean:
	@echo "Cleaning up all executables..."
	@if exist *.exe del *.exe
	@if exist *.o del *.o

# End of Makefile
