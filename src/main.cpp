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

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                generateAndSavePassword(manager);
                break;
            case 2:
                saveExistingPassword(manager);
                break;
            case 3:
                listStoredPasswords(manager);
                break;
            case 4:
                retrievePassword(manager);
                break;
            case 5:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}