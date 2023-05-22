#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    for (unsigned i=0; i<ws.size(); i++) { 
        alphaNum[ws[i]]=i;
    }
    key = convert(getValidKey(skey)); //Cоздание ключа
}

std::string modAlphaCipher::encrypt(const std::string& open_text) //зашифровка
{
    std::vector<int> work = convert(getValidText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size(); //методом гросфельда
    }
    return convert(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    std::vector<int> work = convert(getValidText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size(); 
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::string& s)  // перегрузка
{
    std::vector<int> result; 
    wstring w_s = codec.from_bytes(s); // перекодируем
    for (unsigned i=0; i<w_s.size(); i++) {
        result.push_back(alphaNum[w_s[i]]); //мап в вектор(значения)
    }
    return result;
}

inline std::string modAlphaCipher::convert(const std::vector<int>& v) // перегрузка
{
    std::string result;
    wstring result_s = codec.from_bytes("");
    for (unsigned i=0; i<v.size(); i++) {
        result_s.push_back(ws[v[i]]);
    }
    result = codec.to_bytes(result_s);
    return result;
}

inline std::string modAlphaCipher::getValidKey(const std::string & s) 
{
    if (s.empty())
        throw cipher_error("Empty key");  
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s); //строку в байты
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            tmp[i] = toupper(tmp[i], loc);  //перевод в верхний регистр
        }
        if (ws.find(tmp[i]) == string::npos)
            throw cipher_error(std::string("Invalid key ")+s); //ошибка при неправильном символе
    }
    string tmp1 = codec.to_bytes(tmp); //обратно в байты
    return tmp1;
}

inline std::string modAlphaCipher::getValidText(const std::string & s) //зашифровка текста
{
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    std::wstring n_tmp; 
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            n_tmp.push_back(toupper(tmp[i], loc)); // перевод в верхний регистр и в стринг
        }
        if (ws.find(tmp[i]) != string::npos)
            n_tmp.push_back(tmp[i]);
    }
    string tmp1 = codec.to_bytes(n_tmp);
    if (tmp1.empty())
        throw cipher_error("Empty text");
    return tmp1;
}
