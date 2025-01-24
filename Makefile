# filepath: /home/ash/password-manager/Makefile
# Compiler and Flags
CXX = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source and Object Files
SRC = src/passwordGenerator.cpp src/passwordManager.cpp src/encryption.cpp src/main.cpp src/ui.cpp
OBJ_DIR = build
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

# Target
TARGET = password-manager.exe

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
