CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

SRC = src/passwordGenerator.cpp src/passwordManager.cpp src/encryption.cpp src/main.cpp src/ui.cpp
OBJ_DIR = build
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

TARGET = password-manager.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lssl -lcrypto

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)