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

int main() {
    Control game;
    Menu menu;
    View viewport;

    Dictionary dict;

    Board board;

    game.clearBoard(board);

    string c;
    string resword = "";
    int misx;
    int misy;
    char misch;
    bool didBotSkipTurn = false;
    Coordinates coord;

    while(true) {
        //main menu
        switch(menu.state) {
            case Mainmenu:
            while(true) {
                cout << BOLD "What do you want to do?" RESET << endl;
                cout  << "'" REDC "!" RESET "' to " REDC "exit" RESET ", '" BLUEC "L" RESET "' for " BLUEC "leaderboards" RESET ", " GREENC "any" RESET " key to " GREENC "play" RESET ": ";
                cin >> c;
                if(c.at(0) == '!') {
                    cout << endl;
                    return 0;
                } else if(c.at(0) == 'L') {
                    menu.state = Leaderboardmenu;
                    viewport.refreshScreen();
                    break;
                } else {
                    menu.state =  Settingsmenu;
                    viewport.refreshScreen();
                    break;
                }
                viewport.refreshScreen();
            }
            break;
            case Settingsmenu:
                game.name1 = menu.askName();
                game.isPC = menu.askIsPC();
                if(!game.isPC) {
                    game.name2 = menu.askName(false);
                } else {
                    game.isDifficult = menu.askDifficulty();
                }
                dict.loadDictionary();
                game.centerWord(board, dict.beginningWord);
                game.randomizeFirstPlayer();
                menu.state = Gameplay;
                viewport.refreshScreen();
            break;
            case Gameplay:
            //main game loop
                while(true) {
                    viewport.refreshScreen();
                    if(!game.generateMove(board, dict)) {
                        viewport.endgameScreen(board, dict, game);
                        game.saveGame(board, dict);
                        menu.state = Mainmenu;
                        break;
                    }

                    viewport.displayBoard(board);

                    if(didBotSkipTurn) {
                        cout << "The bot skipped his turn." << endl << endl;
                    } else if (resword!="") {
                        cout << "The bot made the word \"" << resword << "\"." << endl << endl;
                    }

                    viewport.displaySettings(game);
                    cout << endl;
                    viewport.displayWords(dict, game.isPC);
                    cout << endl;
                    viewport.displayScores(dict, game);
                    cout << endl;

                    cout << "Format: " BOLD "3A=X,UL" RESET ";" BOLD " U" RESET "->" UNDERLINE "Up" RESET  
                    BOLD " D" RESET "->" UNDERLINE "Down" RESET  BOLD " L" RESET "->" UNDERLINE "Left" RESET  
                    BOLD " R" RESET "->" UNDERLINE "Right" RESET " Enter '" BOLD "S" RESET "' to " UNDERLINE "skip" RESET " turn" << endl;
                    cout << "P" << ((int)game.isPlayerTurn)+1 <<"'s turn: ";
                    cin >> c;
                    if(c[0] == '!') {
                        viewport.endgameScreen(board, dict, game);
                        game.saveGame(board, dict);
                        menu.state = Mainmenu;
                        break;
                    }

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
            break;
            case Leaderboardmenu:
                while(true) {
                    viewport.refreshScreen();
                    viewport.displayLeaderboards(game);
                    cout << endl;
                    cout << "What do you want to do?" << endl;
                    cout  << "'!' for main menu or enter username to see their best game: ";
                    cin >> c;
                    if(c.at(0) == '!') {
                        viewport.refreshScreen();
                        menu.state = Mainmenu;
                        break;
                    } else {
                        cout << c;
                        Gamedata gd = game.getLeaderboards(c);
                        if(!gd.ignore) {
                            viewport.displayLBGame(gd);
                            cout << endl << endl << endl;
                            cout  << "Press any key to go back to the leaderboards menu: ";
                            cin >> c;
                        }
                    }
                }
            break;
        }
    }

    return 0;
}