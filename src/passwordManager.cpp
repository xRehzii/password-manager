#include "passwordManager.h"
#include "encryption.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <map>

PasswordManager::PasswordManager(const std::string &storageFile, const std::string &keyFile) : storageFile(storageFile), keyFile(keyFile) {}

void PasswordManager::savePassword(const std::string &service, const std::string &username, const std::string &password) {
    std::ifstream inFile(storageFile, std::ios::binary);
    std::ostringstream buffer;
    if (inFile) {
        buffer << inFile.rdbuf();
    }

    std::string encryptedData = buffer.str();
    std::string decryptedData = encryptedData.empty() ? "" : decryptData(encryptedData, keyFile);

    std::map<std::string, std::pair<std::string, std::string>> passwordsStore;
    if (!decryptedData.empty()) {
        std::istringstream stream(decryptedData);
        std::string line;
        while (std::getline(stream, line)) {
            std::istringstream lineStream(line);
            std::string service;
            std::string username;
            std::string password;
            std::getline(lineStream, service, ',');
            std::getline(lineStream, username, ',');
            std::getline(lineStream, password, ',');
            passwordsStore[service] = {username, password};
        }
    }

    passwordsStore[service] = {username, password};

    std::ostringstream outStream;
    for (const auto &[service, credentials] : passwordsStore) {
        outStream << service << ',' << credentials.first << ',' << credentials.second << '\n';
    }

    std::string newEncryptedData = encryptData(outStream.str(), keyFile);
    std::ofstream outFile(storageFile, std::ios::binary);

    if (!outFile) {
        throw std::runtime_error("failed to open storage file to write");
    }

    outFile << newEncryptedData;
}

std::string PasswordManager::getPassword(const std::string &service) {
    std::ifstream inFile(storageFile, std::ios::binary);
    if(!inFile) {
        throw std::runtime_error("failed to open storage file to read");
    }

    std::ostringstream buffer;
    buffer << inFile.rdbuf();
    std::string encryptedData = buffer.str();
    std::string decryptedData = decryptData(encryptedData, keyFile);

    std::map<std::string, std::pair<std::string, std::string>> passwordsStore;
    if (!decryptedData.empty()) {
        std::istringstream stream(decryptedData);
        std::string line;
        while (std::getline(stream, line)) {
            std::istringstream lineStream(line);
            std::string service;
            std::string username;
            std::string password;
            std::getline(lineStream, service, ',');
            std::getline(lineStream, username, ',');
            std::getline(lineStream, password, ',');
            passwordsStore[service] = {username, password};
        }
    }

    if (passwordsStore.find(service) != passwordsStore.end()) {
        return passwordsStore[service].second;
    } else {
        throw std::runtime_error("service not found");
    }
}