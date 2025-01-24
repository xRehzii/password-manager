#include "passwordManager.h"
#include "encryption.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <map>

PasswordManager::PasswordManager(const std::string &storageFile, const std::string &keyFile)
    : storageFile(storageFile), keyFile(keyFile) {
        std::ofstream file(storageFile, std::ios::app);
        if (!file) {
            throw std::runtime_error("failed to create storage file");
        }
}

void PasswordManager::savePassword(const std::string &service, const std::string &username, const std::string &password) {
    std::ofstream file(storageFile, std::ios::app);
    if (!file) {
        throw std::runtime_error("failed to open storage file");
    }
    std::string encryptedPassword = encryptData(password, keyFile);
    file << service << "|" << username << "|" << encryptedPassword << "\n";  // Use '|' as a delimiter
}

std::string PasswordManager::getPassword(const std::string &service) {
    std::ifstream file(storageFile);
    if (!file) {
        throw std::runtime_error("failed to open storage file");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedService, username, encryptedPassword;
        if (std::getline(iss, storedService, '|') && std::getline(iss, username, '|') && std::getline(iss, encryptedPassword)) {
            if (storedService == service) {
                return decryptData(encryptedPassword, keyFile);
            }
        }
    }
    throw std::runtime_error("service not found");
}

std::map<std::string, std::string> PasswordManager::listPasswords() {
    std::ifstream file(storageFile);
    if (!file) {
        throw std::runtime_error("failed to open storage file");
    }
    std::map<std::string, std::string> storedPasswords;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string service, username, encryptedPassword;
        if (std::getline(iss, service, '|') && std::getline(iss, username, '|') && std::getline(iss, encryptedPassword)) {
            storedPasswords[service] = username;
        }
    }
    return storedPasswords;
}

void PasswordManager::deletePassword(const std::string &service) {
    std::ifstream file(storageFile);
    if (!file) {
        throw std::runtime_error("failed to open storage file");
    }
    std::map<std::string, std::string> storedPasswords;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedService, username, encryptedPassword;
        if (std::getline(iss, storedService, '|') && std::getline(iss, username, '|') && std::getline(iss, encryptedPassword)) {
            if (storedService != service) {
                storedPasswords[storedService] = username + "|" + encryptedPassword;
            }
        }
    }
    file.close();

    std::ofstream outFile(storageFile, std::ios::trunc);
    if (!outFile) {
        throw std::runtime_error("failed to open storage file");
    }
    for (const auto &entry : storedPasswords) {
        outFile << entry.first << "|" << entry.second << "\n";
    }
}