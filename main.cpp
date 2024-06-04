#include "includes/board.h"
#include "includes/control.h"
#include "includes/dictionary.h"
#include "includes/move.h"
#include "includes/coordinates.h"
#include "includes/gamedata.h"
#include "includes/view.h"
#include "includes/menu.h"

#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <algorithm> 
#include <iomanip>

#define SIZE 5
#define GOD_WORD "LIGHT"

using namespace std;

int main() {
    Menu menu;

    Dictionary dict;
    dict.loadDictionary();
    
    View viewport;
    Control game;

    Board board;

    game.clearBoard(board);
    game.centerWord(board, dict.beginningWord);

    string c;
    string resword;
    int misx;
    int misy;
    char misch;
    int didBotSkipTurn;

    game.name1 = menu.askName();
    game.isPC = menu.askIsPC();
    if(!game.isPC) {
        game.name2 = menu.askName(false);
    } else {
        game.isDifficult = menu.askDifficulty();
    }
    game.isUkrainian =  menu.askLanguage();
    game.randomizeFirstPlayer();

    while(true) {
        viewport.displayBoard(board);
        if(resword != "") {
            cout << "The bot made the word \"" << resword << "\"." << endl << endl;
        }
        viewport.displaySettings(game);
        cout << endl;
        viewport.displayWords(dict, game.isPC);
        cout << endl;
        viewport.displayScores(dict, game.isPC);
        cout << endl;

        if(!game.generateMove(board, dict)) {
            viewport.refreshScreen();
            viewport.endgameScreen(board, dict, game);
            return 0;
        }
        
        if(didBotSkipTurn) {
            cout << "The bot skipped his turn." << endl << endl;
        }
        cout << "Format: 3A=X,UL; U->Up; D->Down; R->Right; L->Left; Enter 'S' to skip turn" << endl;
        cout << "Your turn: ";
        cin >> c;
        if(c[0] == '!') {
            break;
        }
        
        Coordinates coord;
        if(c[0] != 'S') {
            coord = game.evaluateInput(c);
            if(!coord.ignore) {
                game.place(board, coord, dict);  
                didBotSkipTurn = !game.generateMove(board, dict, resword, misx, misy, misch);
            }
        } else {
            didBotSkipTurn = !game.generateMove(board, dict, resword, misx, misy, misch);
        }


        viewport.refreshScreen();
    }

    return 0;
}