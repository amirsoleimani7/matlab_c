# ===== Compiler detection =====
CXX ?= g++

# ===== Flags =====
CXXFLAGS = -O2 -std=c++17 -Iinclude -Ithird_party
LDFLAGS  =

# ===== Files =====
SRC := $(wildcard src/*.cpp)

# ===== Output =====
EXE := simu
ifeq ($(OS),Windows_NT)
    EXE := simu.exe
endif

BIN := bin/$(EXE)

# ===== Default target =====
all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(BIN)

clean:
	rm -rf bin/simu
	rm -rf bin/Rep/*
	
.PHONY: all clean
