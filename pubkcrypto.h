#ifndef PUBKCRYPTO_H
#define PUBKCRYPTO_H

#include <cstdint>
#include <vector>
#include <random>

class pubkcrypto {

private:
    void selectPrimes(uint32_t* q, uint32_t* p);
    std::mt19937 rng;

public:
    struct PublicKey {
        uint32_t p;
        uint32_t g;
        uint32_t e2;

    };
    struct PrivateKey {
        uint32_t p;
        uint32_t g;
        uint32_t d;
    };
    pubkcrypto(int seed);
    uint32_t getRandom32Bit(uint32_t lower, uint32_t upper);
    uint64_t multiplyAndSquare(uint64_t x, uint64_t y, uint64_t p);
    bool rabinPrimeTest(uint32_t p, int s);
    void generateKeys(struct PublicKey* pub, struct PrivateKey* priv);
    uint32_t GetBlockOfPlainText(std::vector<char>* plainTextBuffer);


};

#endif