# Makefile for compiling and checking memory for a C++11 program

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g  # Enable C++11, all warnings, and debugging info
LDFLAGS = 

# Target program name (replace with your program's name)
TARGET = worddice

# Source file(s)
SRCS = worddice.cpp  # Add other source files if necessary

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target: build the program
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Memory check rule using valgrind
check_memory: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean check_memory
