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

using namespace std;

int main() {
    Menu menu;

    Dictionary dict;
    
    View viewport;
    Control game;

    Board board;

    game.clearBoard(board);

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
    dict.loadDictionary(game.isUkrainian);
    game.centerWord(board, dict.beginningWord);
    game.randomizeFirstPlayer();
    
    //main game loop
    while(true) {
        viewport.refreshScreen();
        if(!game.generateMove(board, dict)) {
            viewport.endgameScreen(board, dict, game);
            return 0;
        }

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

        
        if(didBotSkipTurn) {
            cout << "The bot skipped his turn." << endl << endl;
        }
        cout << "Format: 3A=X,UL; U->Up; D->Down; R->Right; L->Left; Enter 'S' to skip turn" << endl;
        cout << "P" << ((int)game.isPlayerTurn)+1 <<"'s turn: ";
        cin >> c;
        if(c[0] == '!') {
            break;
        }
        
        Coordinates coord;

        if(c[0] != 'S') {
            coord = game.evaluateInput(c);
            if(!coord.ignore) {
                coord.ignore = !game.place(board, coord, dict, game.isPlayerTurn);
                if(!game.isPC && !coord.ignore) {
                    game.isPlayerTurn = !game.isPlayerTurn;
                }
            }
        }

        if(!coord.ignore && game.isPC) {
            didBotSkipTurn = !game.generateMove(board, dict, resword, misx, misy, misch);
        }
    }

    return 0;
}