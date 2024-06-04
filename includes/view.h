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
    int score(bool isUser,Dictionary& dict);
    public:
    void displaySettings(Control& ctrl);
    void displayBoard(Board& board);
    void displayScores(Dictionary& dict, bool isPc);
    void displayWords(Dictionary& dict, bool isPc);
    void refreshScreen() ;
    void endgameScreen(Board& board, Dictionary& dict, Control& ctrl);
};

#endif