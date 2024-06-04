#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;

class Board;
class Dictionary;
class Control;

class Menu {
public:
    bool viewLeaderboards(const string& name);
    bool askLanguage();
    string askName(bool isFirstPlayer = true);
    bool askIsPC();
    bool askDifficulty();
    void exitGame();
    void resetGame(Control ctrl, Dictionary dict, Board board);
};

#endif