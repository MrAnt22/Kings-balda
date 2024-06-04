#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <set>
#include <fstream>

using namespace std;

class View;
class Control;

class Dictionary{
public:
    friend class View;
    friend class Control;
    string beginningWord;
    set<string> words;
    set<string> userWords;
    set<string> pcWords;
    string filename = "dictionary.txt";
    void loadDictionary();
};

#endif