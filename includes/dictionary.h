#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>
#include <fstream>

#define GOD_WORD "LIGHT"
#define DICTEN "dict_en.txt"

using namespace std;

class View;
class Control;

class Dictionary{
private:
public:
    friend class View;
    friend class Control;
    string beginningWord = GOD_WORD;
    unordered_set<string> words;
    unordered_set<string> userWords;
    unordered_set<string> pcWords;
    string filename = DICTEN;
    void loadDictionary();
};

#endif