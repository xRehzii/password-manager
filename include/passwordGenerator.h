#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

#include <string>

std::string generatePassword(int length, bool useSymbols = true, bool useNumbers = true);

#endif