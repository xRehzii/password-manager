#include "encryption.h"
#include <iostream>
#include <cassert>

void testEncryptionDecryption() {
    const std::string keyFile = "test_key.bin";
    const std::string originalText = "This is a test string.";
    std::cout << "Original Text: " << originalText << std::endl;
    std::cout << "Original text length: " << originalText.length() << std::endl;

    generateKey(keyFile);

    std::string encryptedText = encryptData(originalText, keyFile);
    std::cout << "Encrypted text: " << encryptedText << std::endl;
    std::cout << "Encrypted text length: " << encryptedText.length() << std::endl;

    std::string decryptedText = decryptData(encryptedText, keyFile);
    std::cout << "Decrypted text: " << decryptedText << std::endl;
    std::cout << "Decrypted text length: " << decryptedText.length() << std::endl;

    assert(decryptedText == originalText);

    std::cout << "Encryption and decryption test passed!" << std::endl;
}

int main() {
    testEncryptionDecryption();
    return 0;
}