#include "ui.h"
#include "passwordGenerator.h"
#include <iostream>

void displayMenu() {
    std::cout << "Password Manager Menu:\n";
    std::cout << "1. Generate a new password\n";
    std::cout << "2. Store an existing password\n";
    std::cout << "3. List stored passwords\n";
    std::cout << "4. Retrieve a stored password\n";
    std::cout << "5. Delete a stored password\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

void generateAndSavePassword(PasswordManager &manager) {
    std::string service, username;
    int length;
    bool useSymbols, useNumbers;

    std::cout << "\nEnter service name: ";
    std::cin >> service;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password length (12-16 char): ";
    std::cin >> length;
    std::cout << "Use symbols (1 for yes, 0 for no): ";
    std::cin >> useSymbols;
    std::cout << "Use numbers (1 for yes, 0 for no): ";
    std::cin >> useNumbers;

    std::string password = generatePassword(length, useSymbols, useNumbers);
    manager.savePassword(service, username, password);

    std::cout << "Generated password: " << password << "\n";
    std::cout << "Password for " << service << " saved successfully.\n";
}

void saveExistingPassword(PasswordManager &manager) {
    std::string service, username, password;

    std::cout << "\nEnter service name: ";
    std::cin >> service;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    manager.savePassword(service, username, password);
    std::cout << "Password for " << service << " saved successfully.\n";
}

void retrievePassword(PasswordManager &manager) {
    std::map<std::string, std::string> storedPasswords = manager.listPasswords();
    if (storedPasswords.empty()) {
        std::cout << "\nNo passwords in list.\n";
        return;
    }
    std::string service;

    std::cout << "\nEnter service name: ";
    std::cin >> service;

    try {
        std::string password = manager.getPassword(service);
        std::cout << "Retrieved password for " << service << ": " << password << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void listStoredPasswords(PasswordManager &manager) {
    std::map<std::string, std::string> storedPasswords = manager.listPasswords();
    if (storedPasswords.empty()) {
        std::cout << "\nNo passwords stored.\n";
        return;
    } else {
        std::cout << "\nStored passwords:\n";
        for (const auto &entry : storedPasswords) {
        std::cout << "Service: " << entry.first << ", Username: " << entry.second << "\n";
        }
    }
}

void deleteStoredPassword(PasswordManager &manager) {
    std::map<std::string, std::string> storedPasswords = manager.listPasswords();
    if (storedPasswords.empty()) {
        std::cout << "\nNo passwords to delete.\n";
        return;
    }

    std::string service;

    std::cout << "\nEnter service name to delete: ";
    std::cin >> service;

    try {
        manager.deletePassword(service);
        std::cout << "Password for " << service << " deleted successfully.\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}