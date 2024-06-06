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

using namespace std;

class Dictionary;

void View::displaySettings(Control& ctrl) {
    cout << "Lang: [EN], {" << ctrl.name1 << "} playing against {" << (ctrl.isPC ? (ctrl.isDifficult ? "PC on hard diffuculty" : "PC on easy diffuculty") : ctrl.name2) << "}";
}

void View::displayBoard(Board& board){
    cout << "┏━A━┳━B━┳━C━┳━D━┳━E━┓" << endl;
    for(int i = 0; i < board.size; i++) {
        cout << (i+1) << " ";
        for(int j = 0; j < board.size; j++) {
            cout << (board.field[i][j]=='\0' ? ' ' : board.field[i][j]) << " ┃ ";
        }
        cout << endl;
        if(i != board.size-1) {
            cout << "┣━━━╋━━━╋━━━╋━━━╋━━━┫" << endl;
        }
    }
    cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┛" << endl;  
}

void View::displayScores(Dictionary& dict, Control& ctrl) {
    cout << "The P1's score is: {" << ctrl.score(true, dict) << "}\n" << "The " << (ctrl.isPC ? "PC" : "P2") <<"'s score is: {" << ctrl.score(false, dict) << "}\n";
}

void View::displayWords(Dictionary& dict, bool isPc) {
    cout << "P1's discovered words are: {";
    for(auto word: dict.userWords) {
        cout << word << "," ;
    }
    cout << (dict.userWords.size()==0 ? " " : "\b") << "}" << endl;
    cout << (isPc ? "PC" : "P2") << "'s discovered words are: {";
    for(auto word: dict.pcWords) {
        cout << word << "," ;
    }
    cout << (dict.pcWords.size()==0 ? " " : "\b") << "}" << endl;
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
    cout << "------------GAME--------OVER---------------" << endl;
    cout << "Player 1 \"" << ctrl.name1 << "\" scored {" << ctrl.score(true, dict) << "}, ";
    if(ctrl.isPC) {
        cout << "PC scored {" << ctrl.score(false, dict) <<  "}";
    } else {
        cout << "Player 2 \"" << ctrl.name2 << "\" scored {" << ctrl.score(false, dict) <<  "}";
    }
    cout << endl;
    cout << endl;
    this->displayWords(dict, ctrl.isPC);
    cout << endl;

    cout << "";
}