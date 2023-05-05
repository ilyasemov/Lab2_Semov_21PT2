#include <iostream>
#include <cctype>
#include <locale>
#include "Cipher.h"
using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        Cipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = tolower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
}
int main(int argc, char **argv)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wcout<<L'-'<<endl;
    check(L"ВСЕМПРИВЕТ",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    check(L"ВСЕМПРИВЕТ",L"");
    wcout<<L'-'<<endl;
    check(L"ВСЕМПРИВЕТ",L"П1Р2И3В4Е5Т6");
    wcout<<L'-'<<endl;
    check(L"ВСЕМ ПРИВЕТ ЭТО ИЛЬЯ",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    check(L"ВСЕМПРИВЕТЭТО",L"ПРИВЕТ",true);
    wcout<<L'-'<<endl;
    check(L"32131231234353223543",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    return 0;
}
