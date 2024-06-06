#include "control.h"
#include "board.h"
#include "dictionary.h"
#include "menu.h"
#include "view.h"

#include <string>
#include <iostream>

#define REDC "\x1B[31m"
#define GREENC "\x1B[32m"
#define YELLOWC "\x1B[33m"
#define BLUEC "\x1B[34m"
#define MAGENTAC "\x1B[35m"
#define CYANC "\x1B[36m"
#define LIGHTGRAYC "\x1B[37m"

#define BG_GREENC "\x1B[42m"
#define BG_YELLOWC "\x1B[43m"
#define BG_BLUEC "\x1B[44m"
#define BG_MAGENTAC "\x1B[45m"
#define BG_CYANC "\x1B[46m"
#define BG_LIGHTGRAYC "\x1B[47m"

#define BOLD "\x1B[1m"
#define UNDERLINE "\x1B[4m"
#define RESET "\x1B[0m"


using namespace std;

class Board;
class Dictionary;
class Control;

string Menu::askName(bool isFirstPlayer){
    string name;
    cout << (isFirstPlayer ? "Enter " BLUEC "P1" RESET  "'s name: " : "Enter " YELLOWC "P2" RESET "name: ");
    cin >> name;
    return name;
}

bool Menu::askIsPC(){
    string ch;
    cout << "Type any symbol for pc, or type '1' second player: ";
    cin >> ch;
    return (ch.at(0) != '1');
}

bool Menu::askDifficulty(){
    string ch;
    cout << "Type any symbol for easy difficulty, or type '1' for hard difficulty: ";
    cin >> ch;
    return (ch.at(0) == '1');
}

void Menu::exitGame(){
    cout << "Want to restart?" << endl;
    cout << "Y(yes)" << "\t" << "N(no)\n";
    string ch;
    cin >> ch;
    if (ch.at(0) == L'Y' || ch.at(0) == L'y'){
        cout << "restarting game";
        //якось запуститься знову
    }
    else if (ch.at(0) == L'N' || ch.at(0) == L'n'){
        cout << "closing...";
        //закриється
    }
    else{
        cout << "error(try to write N-for close or Y-to restart)";
    }
}

void Menu::resetGame(Control ctrl, Dictionary dict, Board board){
    
}