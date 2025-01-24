#ifndef UI_H
#define UI_H

#include "passwordManager.h"
void displayMenu();
void generateAndSavePassword(PasswordManager &manager);
void saveExistingPassword(PasswordManager &manager);
void retrievePassword(PasswordManager &manager);
void listStoredPasswords(PasswordManager &manager);
void deleteStoredPassword(PasswordManager &manager);

#endif