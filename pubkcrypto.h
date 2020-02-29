#ifndef PUBKCRYPTO_H
#define PUBKCRYPTO_H

#include <cstdint>

class pubkcrypto {

public:
    uint64_t getRandom32Bit(uint64_t lower, uint64_t upper);
    uint64_t power(uint64_t x, uint64_t y, uint64_t p);
    bool rabinPrimeTest(uint64_t p, int s);
    void generateKeys(uint64_t* pub, uint64_t* priv);
    void selectPrimes(uint64_t * q, uint64_t * p);


};

#endif