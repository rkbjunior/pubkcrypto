#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
//#include <experimental/filesystem>  //for linux
#include <filesystem>  // for windows
#include "helpers.h"
#include "fileio.h"

using namespace std;

void fileio::GetPlainTextFromFile(vector<char>* plainTextBuffer, string fileName) {
    ifstream plaintextFile(fileName, ios::in | ios::binary | std::ios::ate);
    streamsize psize = plaintextFile.tellg();

    while (psize % 4 != 0) {

        psize++;
    }

    plainTextBuffer->resize(psize);

    plaintextFile.seekg(0, std::ios::beg);

    plaintextFile.read(plainTextBuffer->data(), psize);

}

void fileio::GetCipherTextFromFile(vector<uint32_t>* cipherTextBuffer, string fileName) {
    ifstream ciphertextFile;
    ciphertextFile.open(fileName, ios::in | ios::binary);

    uint64_t result = 0;

    while (!ciphertextFile.eof()) {
        ciphertextFile >> std::hex;
        ciphertextFile >> result;

        cipherTextBuffer->push_back(result);
    }
    cipherTextBuffer->pop_back();
}

void fileio::WriteToFile(uint32_t ciphertext,uint32_t ciphertext2, string fileName) {
    ofstream outputFile;
    helpers help;

    outputFile.open(fileName, ios::out | ios::binary | ios::app);

    if (fileName == "ctext.txt") {
        outputFile << ciphertext  << " " << ciphertext2 << "\n";
    }
    else {
        string ptext = help.Convert32ToString(ciphertext);
        outputFile << ptext;
    }

}

void fileio::WriteKeys(uint32_t p, uint32_t g, uint32_t e2, uint32_t d) {
    ofstream outputFilePub, outputFilePri;
    helpers help;

    outputFilePub.open("pubkey.txt", ios::out | ios::binary | ios::app);
    outputFilePub << p << " " << g << " " << e2;
    outputFilePri.open("prikey.txt", ios::out | ios::binary | ios::app);
    outputFilePri << p << " " << g << " " << d;
}

void fileio::GetKeyFromFile(string fileName, uint32_t* p, uint32_t* g, uint32_t* ed) {
    ifstream keyFile;
    keyFile.open(fileName, ios::in | ios::binary);

    keyFile >> *p >> *g >> *ed;
}