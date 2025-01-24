#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string> 
#include <map>

class PasswordManager {
public:
    PasswordManager(const std::string &storageFile, const std::string &keyFile);
    void savePassword(const std::string &service, const std::string &username, const std::string &password);
    std::string getPassword(const std::string &service);
    std::map<std::string, std::string> listPasswords();
    void deletePassword(const std::string &service);

private:
    std::string storageFile;
    std::string keyFile;
};

#endif