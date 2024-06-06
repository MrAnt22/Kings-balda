#ifndef VIEW_H
#define VIEW_H

#include <set>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Board;
class Coordinates;
class Dictionary;
class Control;

class View {
    public:
    void displaySettings(Control& ctrl);
    void displayBoard(Board& board);
    void displayScores(Dictionary& dict, Control& ctrl);
    void displayLeaderboards(Control& ctrl);
    void displayWords(Dictionary& dict, bool isPc);
    void refreshScreen() ;
    void endgameScreen(Board& board, Dictionary& dict, Control& ctrl);
    void displayLBGame(Gamedata gd);
};

#endif