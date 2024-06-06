#include "dictionary.h"

#include <string>
#include <set>
#include <fstream>
#include <iostream>

#define GOD_WORD "LIGHT"
#define DICTEN "dict_en.txt"

class View;
class Control;

void Dictionary::loadDictionary() {     
    srand(time(0)); 

    string word;
    ifstream dict(filename);

    while(getline(dict, word)) {
        for (auto& x : word) {
            x = toupper(x);
        }
        words.insert(word);

        if((word.length() == 5 && beginningWord == GOD_WORD) && (rand()%20) == 0 ) {
            beginningWord = word;
        }
    }
    dict.close();
}