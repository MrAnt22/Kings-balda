#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <set>
#include <fstream>

#define GOD_WORD "LIGHT"
#define DICTEN "dict_en.txt"
#define DICTUA "dict_ua.txt"

using namespace std;

class View;
class Control;

class Dictionary{
private:
public:
    friend class View;
    friend class Control;
    string beginningWord = GOD_WORD;
    set<string> words;
    set<string> userWords;
    set<string> pcWords;
    string filename = DICTEN;
    void loadDictionary(bool isUkrainian = false);
};

#endif