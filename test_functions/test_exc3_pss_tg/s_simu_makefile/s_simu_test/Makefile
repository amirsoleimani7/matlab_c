# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2 -Iinclude -MMD -MP

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Find all source files and create lists of object files and dependency files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

# Executable
EXEC = $(BIN_DIR)/test_program

# Create necessary directories if they don't exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Main target: build the executable
all: $(EXEC)

# Link all object files to produce the executable
$(EXEC): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXEC)

# Compile source files to object files and generate dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include automatically generated dependency files (if they exist)
-include $(DEP_FILES)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the executable
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
