#ifndef ENCRIPTION_H
#define ENCRIPTION_H

#include <string>
void generateKey(const std::string &keyFile);

std::string encryptData(const std::string &data, const std::string &keyFile);
std::string decryptData(const std::string &data, const std::string &keyFile);

#endif