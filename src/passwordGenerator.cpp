#include "passwordGenerator.h"
#include <iostream>
#include <string>
#include <random>

std::string generatePassword(int length, bool useSymbols, bool useNumbers) {
    const int minLength = 12;
    const int maxLength = 16;

    if (length < minLength) {
        length = minLength;
    } else if (length > maxLength) {
        length = maxLength;
    }
    
    const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string symbols = "!@#$%^&*()_-+={}[]<>.?";
    const std::string numbers = "0123456789";

    std::string characters = letters; 
    if (useNumbers) {
        characters = characters + numbers;
    }
    if (useSymbols) {
        characters = characters + symbols;
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string password;
    for (int i = 0; i < length; i++) {
        password = password + characters[distribution(generator)];
    }

    return password;
}