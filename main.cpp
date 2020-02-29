#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <random>
#include "globals.h"
#include "pubkcrypto.h"

using namespace std;

int LOGGING = 0;
int SEED = 10;
mt19937 rng(SEED);

int main()
{
    //If the ciphertext.txt exists, delete it.
    if (LOGGING > 0)
        cout << "Cleaning up some stuff...\n";

    if (remove("ciphertext.txt") == 0) {
        if (LOGGING > 0)
            cout << "Deleted ciphertext.txt\n";
    }
    else {
        if (LOGGING > 0)
            cout << "ciphertext.txt was not found or has open handles\n";
    }

    //If the decrypted_plaintext.txt exists, delete it.
    if (remove("decrypted_plaintext.txt") == 0) {
        if (LOGGING > 0)
            cout << "Deleted decrypted_plaintext.txt\n\n";
    }
    else {
        if (LOGGING > 0)
            cout << "decrypted_plaintext.txt was not found or has open handles\n\n";
    }

    int option;
    bool running = true;
    pubkcrypto crypto;
    uint64_t p, q;

    while (running != false) {
        cout << "*******************************\n";
        cout << " 1 - Key Generation.\n";
        cout << " 2 - Encrypt a file.\n";
        cout << " 3 - Decrypt a file.\n";
        cout << " 4 - Turn off Verbose Logging.\n";
        cout << " 5 - Exit.\n";
        cout << " Enter your choice and press return: ";

        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        cout << endl;

        switch (option)
        {
        case 1:
            cout << "Key Generation.\n\n";
            // rest of code here
            
            
            crypto.selectPrimes(&p, &q);

            break;
        case 2:
            cout << "Encrypt a file.\n\n";
            // rest of code here
            break;
        case 3:
            cout << "Decrypt a file.\n\n";
            break;
        case 4:
            cout << "Change Log Options [0: NONE, 1: INFO, 2: VERBOSE]\n";
            cin >> LOGGING;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << endl;
            break;
        case 5:
            cout << "End of Program.\n";
            running = false;
            break;
        default:
            cout << "Not a Valid Choice. \n";
            cout << "Choose again.\n\n";
            break;
        }
    }

    cout << "Good Bye from PSU_CRYPT!" << endl;
    return 0;
}

