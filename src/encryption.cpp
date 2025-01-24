#include "encryption.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <openssl/evp.h>
#include <openssl/rand.h>   

const int keySize = 32;
const int ivSize = 16;

void generateKey(const std::string &keyFile) {
    unsigned char key[keySize];
    if (!RAND_bytes(key, keySize)) {
        throw std::runtime_error("key generation failed");
    }

    std::ofstream file(keyFile, std::ios::binary);

    if (!file) {
        throw std::runtime_error("failed to open key file");
    }

    file.write(reinterpret_cast<char*>(key), keySize);
}

std::string loadKey(const std::string &keyFile) {
    std::ifstream file(keyFile, std::ios::binary);

    if (!file) {
        throw std::runtime_error("failed to open key file");
    }

    unsigned char key[keySize];

    file.read(reinterpret_cast<char*>(key), keySize);
    return std::string(reinterpret_cast<char*>(key), keySize);
}

std::string encryptData(const std::string &data, const std::string &keyFile) {
    auto key = loadKey(keyFile);

    unsigned char initializationVector[ivSize];
    if (!RAND_bytes(initializationVector, ivSize)) {
        throw std::runtime_error("initialization vector generation failed");
    }

    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(context, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), initializationVector);

    std::string encryptedData;
    encryptedData.resize(data.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));

    int encryptBytes;
    EVP_EncryptUpdate(context, reinterpret_cast<unsigned char*>(&encryptedData[0]), &encryptBytes, reinterpret_cast<const unsigned char*>(data.data()), data.size());

    int finalBytes;
    EVP_EncryptFinal_ex(context, reinterpret_cast<unsigned char*>(&encryptedData[0]) + encryptBytes, &finalBytes);

    EVP_CIPHER_CTX_free(context);

    encryptedData.resize(encryptBytes + finalBytes);

    return std::string(reinterpret_cast<char*>(initializationVector), ivSize) + encryptedData;
}

std::string decryptData(const std::string &encryptedData, const std::string &keyFile) {
    auto key = loadKey(keyFile);

    unsigned char initializationVector[ivSize];
    std::copy(encryptedData.begin(), encryptedData.begin() + ivSize, initializationVector);

    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(context, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.data()), initializationVector);

    std::string decryptedData;
    decryptedData.resize(encryptedData.size() - ivSize);

    int decryptBytes;
    EVP_DecryptUpdate(context, reinterpret_cast<unsigned char*>(&decryptedData[0]), &decryptBytes, reinterpret_cast<const unsigned char*>(encryptedData.data() + ivSize), encryptedData.size() - ivSize);

    int finalBytes;
    EVP_DecryptFinal_ex(context, reinterpret_cast<unsigned char*>(&decryptedData[0]) + decryptBytes, &finalBytes);

    EVP_CIPHER_CTX_free(context);

    decryptedData.resize(decryptBytes + finalBytes);

    return decryptedData;
}