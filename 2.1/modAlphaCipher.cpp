#include "modAlphaCipher.h"

std::string modAlphaCipher::encrypt(const std::string& open_text)
{
    string s = getValidText(open_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[k] = s[index-1];
                k++;
            }
        }
    }
    return n_s;
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    string s = getValidText(cipher_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[index-1] = s[k];
                k++;
            }
        }
    }
    return n_s;
}

inline std::string modAlphaCipher::getValidText(const std::string & s)
{
    std::string tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}
