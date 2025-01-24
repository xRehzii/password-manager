# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source and Object Files
SRC = src/passwordGenerator.cpp src/passwordManager.cpp src/encryption.cpp src/main.cpp
OBJ_DIR = build
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

# Target
TARGET = password-manager

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lssl -lcrypto

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
