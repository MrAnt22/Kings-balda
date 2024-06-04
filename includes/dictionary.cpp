#include "dictionary.h"

#include <string>
#include <set>
#include <fstream>
#include <iostream>

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
        words.insert(word.substr(0,word.length()));

        if((word.size() == 5 && beginningWord == "") && (rand()%20) == 0 ) {
            beginningWord = word;
        }
    }
    dict.close();
}