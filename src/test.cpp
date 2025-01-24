#include "passwordGenerator.h"
#include "passwordManager.h"
#include "encryption.h"
#include "ui.h"
#include <iostream>

int main() {
    const std::string keyFile = "data/keyfile.key";
    const std::string storageFile = "data/passwords.enc";

    try {
        generateKey(keyFile);
        std::cout << "Key generated successfully. \n" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Key generation failed: " << e.what() << std::endl;
        return 1;
    }

    PasswordManager manager(storageFile, keyFile);

    try {
        std::string service = "Google";
        std::string username = "johnSmith@gmail.com";
        std::string password = generatePassword(16, true, true);

        std::cout << "Generated password:" << password << std::endl;
        manager.savePassword(service, username, password);
        std::cout << "Password for " << service << " saved successfully." << std::endl;

        std::string retrievedPassword = manager.getPassword(service);
        std::cout << "Retrieved password for " << service << " is:" << retrievedPassword << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Password manager failed: " << e.what() << std::endl;
        return 1;
    }
}