#include "control.h"
#include "board.h"
#include "dictionary.h"
#include "menu.h"

#include <string>
#include <iostream>

using namespace std;

class Board;
class Dictionary;
class Control;

bool Menu::viewLeaderboards(const string& name) {
    cout << "Here's leaderboard:" << endl;
    string leaders;
    ifstream leaderboards("leaderboards.txt");
    while (getline (leaderboards, leaders)){
        cout << leaders << endl;
    }
    leaderboards.close();
    return true;
}

bool Menu::askLanguage(){
    string lan;
    cout << "Type 1 for English, any other symbol for Ukrainian: ";
    cin >> lan;
    if(lan[0] == '1'){
        return false;
    } else {
        return true;
    }
}

string Menu::askName(bool isFirstPlayer){
    string name;
    cout << (isFirstPlayer ? "Enter P1 name: " : "Enter P2 name: ");
    cin >> name;
    return name;
}

bool Menu::askIsPC(){
    string ch;
    cout << "Type 1 to play against PC, any other symbol for second player: ";
    cin >> ch;
    if (ch[0] == '1'){
        return true;
    }
    else{ 
        return false;
    }
}

bool Menu::askDifficulty(){
    string ch;
    cout << "Type 1 for easy difficulty, any other symbol for hard difficulty: ";
    cin >> ch;
    if (ch[0] == '1'){
        return false;
    }
    else{ 
        return true;
    }
}

void Menu::exitGame(){
    cout << "want to restart?" << endl;
    cout << "Y(yes)" << "\t" << "N(no)\n";
    string ch;
    cin >> ch;
    if (ch[0] == 'Y' || ch[0] == 'y'){
        cout << "restarting game";
        //якось запуститься знову
    }
    else if (ch[0] == 'N' || ch[0] == 'n'){
        cout << "closing...";
        //закриється
    }
    else{
        cout << "error(try to write N-for close or Y-to restart)";
    }
}

void Menu::resetGame(Control ctrl, Dictionary dict, Board board){
    
}