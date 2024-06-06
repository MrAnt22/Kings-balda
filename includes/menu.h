#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;

class Board;
class Dictionary;
class Control;

enum Gamestate {
    Mainmenu = 0, Settingsmenu = 1, Gameplay = 2, Leaderboardmenu = 3
};

class Menu {
public:
    int state = Mainmenu;
    string askName(bool isFirstPlayer = true);
    bool askIsPC();
    bool askDifficulty();
    void exitGame();
    void resetGame(Control ctrl, Dictionary dict, Board board);
};

#endif