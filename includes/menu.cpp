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
    cout << "Type " CYANC "any" RESET " symbol for pc, or type '" GREENC "1" RESET "' for second player: ";
    cin >> ch;
    return (ch.at(0) != '1');
}

bool Menu::askDifficulty(){
    string ch;
    cout << "Type " CYANC "any" RESET "symbol for" CYANC "easy" RESET "difficulty, or type '" REDC "1" RESET "' for" REDC  "hard" RESET "difficulty: ";
    cin >> ch;
    return (ch.at(0) == '1');
}

void Menu::MainMenu() {
    cout << BOLD "What do you want to do?" RESET << endl;
    cout  << "'" REDC "!" RESET "' to " REDC "exit" RESET ", '" BLUEC "L" RESET "' for " BLUEC "leaderboards" RESET ", " GREENC "any" RESET " key to " GREENC "play" RESET ": ";
}

void Menu::LeaderboardsMenu() {
        cout << "What do you want to do?" << endl;
        cout  << "'!' for main menu or enter username to see their best game: ";
}

void Menu::LbsGoBack() {
    cout  << "Press any key to go back to the leaderboards menu: ";
}

void Menu::userEnterMove(bool isPlayerTurn) {
    cout << "Format: " BOLD "3A=X,UL" RESET ";" BOLD " U" RESET "->" UNDERLINE "Up" RESET  
    BOLD " D" RESET "->" UNDERLINE "Down" RESET  BOLD " L" RESET "->" UNDERLINE "Left" RESET  
    BOLD " R" RESET "->" UNDERLINE "Right" RESET " Enter '" BOLD "S" RESET "' to " UNDERLINE "skip" RESET " turn" << endl;
    cout << "P" << ((int)isPlayerTurn)+1 <<"'s turn: ";
}