#include "pubkcrypto.h"
#include <random>
#include <iostream>
#include <cmath>
#include "globals.h"

using namespace std;

uint64_t pubkcrypto::getRandom32Bit(uint64_t lower, uint64_t upper)
{
    //minimum 2147483648 and maximum 4294967295
    uniform_int_distribution<uint32_t> distribution(lower, upper);
    return distribution(rng);
}

// Utility function to do modular exponentiation. 
// aka Square and multiply
// It returns (x^y) % p 
// https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
uint64_t pubkcrypto::power(uint64_t x, uint64_t y, uint64_t p) 
{
    uint64_t res = 1;
    x = x % p;  

    while (y > 0)
    {
        if (y & 1)
        {
            res = (res * x) % p;
        }

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

bool pubkcrypto::rabinPrimeTest(uint64_t n, int s) 
{
    uint64_t primeCandidate = n - 1;

    while (primeCandidate % 2 == 0)
    {
        primeCandidate /= 2;
    }

    //for i = 1 to security parameter s
    for (int i = 0; i < s; i++) 
    {
        //get random a from 2 to n-2
        uint64_t a = getRandom32Bit(2, n - 2);


        uint64_t z = power(a, primeCandidate, n);

        if (z == 1 || z == n - 1)
        {
            return true;
        }

        while (primeCandidate != n-1)
        {
            z = (z * z) % n;
            primeCandidate *= 2;

            if (z == 1)
            {
                return false;
            }

            if (z == n - 1)
            {
                return true;
            }
        }
    }

    return false;

}

void pubkcrypto::selectPrimes(uint64_t * q, uint64_t * p) {

    bool isPrime = false;
    while (!isPrime)
    {
        *q = getRandom32Bit(2147483648, 4294967295);
        if (rabinPrimeTest(*q, 4)) {
            if (*q % 12 != 5) {
                *p = 2 * *q + 1;
                if (rabinPrimeTest(*p, 4)) {
                    isPrime = true;
                    return;
                }
            }
        }
    }
}