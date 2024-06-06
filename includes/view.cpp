#include "control.h"
#include "board.h"
#include "coordinates.h"
#include "dictionary.h"
#include "view.h"

#include <set>
#include <string>
#include <fstream>
#include <algorithm>
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

class Dictionary;

void View::displaySettings(Control& ctrl) {
    cout << BOLD "" << ctrl.name1 << RESET " playing against " BOLD << (ctrl.isPC ? (ctrl.isDifficult ? "PC (" REDC "hard" RESET " difficulty)" : "PC ("  "easy" " difficulty)") : (ctrl.name2)) <<  RESET "";
}

void View::displayBoard(Board& board){
    cout <<  "┏━A━┳━B━┳━C━┳━D━┳━E━┓"  << endl;
    for(int i = 0; i < board.size; i++) {
        cout << (i+1) <<  " ";
        for(int j = 0; j < board.size; j++) {
            if(board.p1Move.x == i && board.p1Move.y == j) {
                cout << BOLD;
            } else if(board.p2Move.x == i && board.p2Move.y == j) {
                cout << BOLD;
            } 
            if(board.isP1[i][j] == 1) {
                cout << YELLOWC;
            } else if(board.isP1[i][j] == 2) {
                cout << BLUEC;
            } else {
                cout << CYANC;
            }
            cout << (board.field[i][j]=='\0' ? ' ' : board.field[i][j]);
            cout <<  RESET " ┃ " ;
        }
        cout << endl;
        if(i != board.size-1) {
            cout <<  "┣━━━╋━━━╋━━━╋━━━╋━━━┫"  << endl;
        }
    }
    cout <<  "┗━━━┻━━━┻━━━┻━━━┻━━━┛"  << endl;  
}

void View::displayScores(Dictionary& dict, Control& ctrl) {
    cout << "The " BLUEC "P1" RESET "'s score is: {" BLUEC << ctrl.score(true, dict) << RESET "}\n" << "The " YELLOWC << (ctrl.isPC ? "PC" : "P2") << RESET "'s score is: {" YELLOWC << ctrl.score(false, dict) << RESET "}\n";
}

void View::displayWords(Dictionary& dict, bool isPc) {
    cout << BLUEC "P1" RESET "'s discovered words are: {" BLUEC;
    for(auto word: dict.userWords) {
        cout << word << "," ;
    }
    cout << (dict.userWords.size()==0 ? " " : "\b") << RESET "}" << endl;
    cout << YELLOWC <<  (isPc ? "PC" : "P2") << RESET "'s discovered words are: {" YELLOWC;
    for(auto word: dict.pcWords) {
        cout << word << "," ;
    }
    cout << (dict.pcWords.size()==0 ? " " : "\b") << RESET "}" << endl;
}

void View::refreshScreen() {
    cout << "\x1B[2J\x1B[H";
}

void View::displayLeaderboards(Control& ctrl) {
    vector<Gamedata> lbs = ctrl.getLeaderboards();
    for(Gamedata gd: lbs) {
        cout << gd.p1name  << " {" << gd.p1score << "} vs " << (gd.isPC?"PC":gd.p2name) << " {" << gd.p2score << "}" << endl;
    }
}

void View::displayLBGame(Gamedata gd) {
    refreshScreen();
    displayBoard(gd.board);
    cout << gd.p1name  << " {" << gd.p1score << "} vs " << (gd.isPC?"PC":gd.p2name) << " {" << gd.p2score << "}" << endl;
}

void View::endgameScreen(Board& board, Dictionary& dict, Control& ctrl) {
    this->displayBoard(board);
    cout << endl << endl;
    cout << BOLD MAGENTAC "------------GAME--------------OVER---------------" RESET << endl;
    cout << "Player 1 \"" BOLD << ctrl.name1 << RESET  "\" scored {" BLUEC << ctrl.score(true, dict) << RESET "}, ";
    if(ctrl.isPC) {
        cout << BOLD "PC" RESET "scored {" YELLOWC << ctrl.score(false, dict) << RESET  "}";
    } else {
        cout << "Player 2 \"" BOLD << ctrl.name2 << RESET "\" scored {" << YELLOWC << ctrl.score(false, dict) <<  RESET "}";
    }
    cout << endl;
    cout << endl;
    this->displayWords(dict, ctrl.isPC);
    cout << endl;

    cout << "";
}