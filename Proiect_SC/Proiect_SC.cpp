// Proiect_SC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RSA.h"
#include "Blowfish.h"
#include "IDEA.h"
#include <string>

#define TEST_STRING "aLorem ipsum dollor sit ametul NaaahZz.,?!()abcdefghijklmnop"


using namespace std;



int main()
{
    //  RSA ---------------------------------------
    //  seed este p=3, q=11
    cout << "RSA ALGORITHM:" << endl;
    Key privateKey = RSA::generatePrivateKey(3, 11);
    Key publicKey = RSA::generatePublicKey(3, 11);
    RSA RSAtest = RSA(publicKey, TEST_STRING);
    RSAtest.setPrivateKey(privateKey);

    string encryptedRSA = RSAtest.crypt();
    cout << "Encrypted: " << encryptedRSA << endl;
    cout << "Decrypted: " << RSAtest.decrypt(encryptedRSA) << endl;
    cout << endl << endl;
    
    //  Blowfish ----------------------------------
    cout << "Blowfish ALGORITHM:" << endl;
    Blowfish Blowfishtest = Blowfish(TEST_STRING);
    string Blowfishencr = Blowfishtest.getEncryptedMessage();
    string blowfishdecr = Blowfishtest.decrypt();
    cout <<"Encrypted: " << Blowfishencr << endl;
    cout << "Decrypted: " << blowfishdecr << endl;
    cout << endl << endl;


    //  IDEA ---------------------------------------
    cout << "IDEA ALGORITHM:" << endl;
    IDEA ideatest = IDEA();
    ideatest.setMessage(TEST_STRING);
    ideatest.setKey("ZZZZefghijklmnop");
    string ideaencr = ideatest.encrypt();
    string ideadecr = ideatest.decrypt(ideaencr);
    cout << "Encrypted: " << ideaencr << endl;
    cout << "Decrypted: " << ideadecr << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

