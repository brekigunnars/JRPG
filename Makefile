# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Executable name
TARGET = game

# Source files
SRC = coolGameBruh.cpp
OBJ = $(SRC:.cpp=.o)

# Default target (compiles the game)
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game after compiling
run: all
	./$(TARGET)

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)
