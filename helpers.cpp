#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include "helpers.h"

using namespace std;

/*
Converts a uint64_t into an ascii equivalent string

Param: value -  a uint64_t value to be converted

Returns: An ascii representation of a uint64_t
*/
string helpers::Convert32ToString(uint32_t value) {
    string result;

    for (int i = 3; i >= 0; i--) {
        result.push_back(value >> (i * 8) & 0x000000FF);
    }

    return result;
}