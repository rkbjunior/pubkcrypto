#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <random>
#include "globals.h"
#include "pubkcrypto.h"
#include "fileio.h"

using namespace std;

int LOGGING = 0;
int SEED = 10;
mt19937 rng(SEED);

int main()
{
    //If the ciphertext.txt exists, delete it.
    if (LOGGING > 0)
        cout << "Cleaning up some stuff...\n";

    if (remove("ctext.txt") == 0) {
        if (LOGGING > 0)
            cout << "Deleted ciphertext.txt\n";
    }
    else {
        if (LOGGING > 0)
            cout << "ciphertext.txt was not found or has open handles\n";
    }

    if (remove("pubkey.txt") == 0) {
        if (LOGGING > 0)
            cout << "Deleted pubkey.txt\n";
    }
    else {
        if (LOGGING > 0)
            cout << "pubkey.txt was not found or has open handles\n";
    }

    if (remove("prikey.txt") == 0) {
        if (LOGGING > 0)
            cout << "Deleted prikey.txt\n";
    }
    else {
        if (LOGGING > 0)
            cout << "prikey.txt was not found or has open handles\n";
    }

    //If the decrypted_plaintext.txt exists, delete it.
    if (remove("dtext.txt") == 0) {
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
    pubkcrypto::PrivateKey privKey;
    pubkcrypto::PublicKey pubKey;
    fileio file;
    vector<char> ptextBuffer;
    string fileName;
    string keyFileName;
    fstream infile;

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
            crypto.generateKeys(&pubKey, &privKey);

            cout << "Public Key: (" << pubKey.p << "," << pubKey.g << "," << pubKey.e2 << ")\n\n";
            cout << "Private key: (" << pubKey.p << "," << pubKey.g << "," << privKey.d << ")\n\n";

            file.WriteKeys(pubKey.p, pubKey.g, pubKey.e2, privKey.d);

            break;
        case 2:
            cout << "Encrypt a file.\n\n";
            cout << " Enter the file name you would like to encrypt [default ptext.txt] : ";
            getline(cin, fileName);
            cout << endl;
            cout << " Enter the file name that contains the hex formatted key [default pubkey.txt] : ";
            getline(cin, keyFileName);

            if (!fileName.length() > 0)
                fileName = "ptext.txt";
            if (!keyFileName.length() > 0)
                keyFileName = "pubkey.txt";

            file.GetPlainTextFromFile(&ptextBuffer, fileName);
            file.GetKeyFromFile(keyFileName, &pubKey.p, &pubKey.g, &pubKey.e2);

            while (ptextBuffer.size() > 0) {
                uint32_t plaintextBlock = crypto.GetBlockOfPlainText(&ptextBuffer);
                ptextBuffer.erase(ptextBuffer.begin(), ptextBuffer.begin() + 4);

                uint32_t r = crypto.getRandom32Bit(1, pubKey.p - 1);
                while (!crypto.rabinPrimeTest(r, 4)) {
                    r = crypto.getRandom32Bit(1, pubKey.p - 1);
                }

                uint32_t c1 = crypto.multiplyAndSquare((uint64_t)pubKey.g, (uint64_t)r, (uint64_t)pubKey.p);
                uint32_t c2 = plaintextBlock * (crypto.multiplyAndSquare((uint64_t)pubKey.e2, (uint64_t)r, (uint64_t)pubKey.p)) % pubKey.p;

                cout << "c1:" << c1 << " c2:" << c2 <<  "\n\n";

                file.WriteToFile(c1,c2, "ctext.txt");

            }

            break;
        case 3:
            cout << "Decrypt a file.\n\n";

            uint32_t c1, c2, r;
            uint32_t ptext;
            file.GetKeyFromFile("privkey.txt", &privKey.p, &privKey.g, &privKey.d);

            r = privKey.p - 1 - privKey.d;

            infile.open("ctext.txt", ios::in);
            while (infile >> c1 >> c2)
            {
                ptext = c2 * (crypto.multiplyAndSquare((uint64_t)c1, (uint64_t)r, (uint64_t)privKey.p)) % privKey.p;
                file.WriteToFile(ptext, 0, "dtext.txt");
            }

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

