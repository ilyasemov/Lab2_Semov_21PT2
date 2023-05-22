#include  "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>

void check(const string& Text, const string& key)
{
    try {
        string cipherText;
        string decryptedText;
        modAlphaCipher cipher(key); //Оъект класса
        cipherText = cipher.encrypt(Text);
        decryptedText = cipher.decrypt(cipherText);
        cout<<"key="<<key<<endl;
        cout<<"Encrypted text: "<<cipherText<<endl;
        cout<<"Decrypted text: "<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
    cout<<""<<endl;
}

int main(int argc, char **argv)
{
    check("ПОКА","Привет");
    check("ПОКА","");
    check("ПОКА","ПРИВЕТ123");
    check("П о к а","ПРИВЕТ");
    check("123","ПРИВЕТ");
}
