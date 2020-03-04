#ifndef FILEIO_H
#define FILEIO_H

class fileio {
public:
    void WriteToFile(uint32_t ciphertext, uint32_t ciphertext2, std::string fileName);
    void GetKeyFromFile(std::string fileName, uint32_t * p, uint32_t * g, uint32_t * ed);
    void GetPlainTextFromFile(std::vector<char>* plainTextBuffer, std::string fileName);
    void GetCipherTextFromFile(std::vector<uint32_t>* cipherTextBuffer, std::string fileName);
    void WriteKeys(uint32_t p, uint32_t g, uint32_t e2, uint32_t d);
};
#endif