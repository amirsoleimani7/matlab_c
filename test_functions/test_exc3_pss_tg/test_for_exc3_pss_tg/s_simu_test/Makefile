# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Directories
SRC_DIR = .
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Files
SRC_FILES = $(SRC_DIR)/test_s_simu.cpp
OBJ_FILES = $(OBJ_DIR)/test_s_simu.o
EXEC = $(BIN_DIR)/test_program

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Targets
all: $(EXEC)

# Link the object files into the executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ_FILES)

# Compile the source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/test_program

# Run the executable
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
