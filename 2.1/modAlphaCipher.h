#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cctype>
using namespace std;
class modAlphaCipher
{
private:
    int key;
    std::string getValidText(const std::string & s);
public:
    modAlphaCipher()=delete;
    modAlphaCipher(const int& key1) :key(key1) {};
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
