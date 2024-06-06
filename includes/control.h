#ifndef CONTROL_H
#define CONTROL_H

#include "gamedata.h"

#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Board;
class Coordinates;
class Dictionary;

class Control {
    private: 
        bool canFormWord(Board& board, const string& word, int i, int j);
        bool dfs(Board& board, const string& word, int r, int c, int index);
    public:
        bool isFirstPlayerFirst = true;
        bool isPlayerTurn = false;
        string name1 = "Name";
        string name2 = "Tyler Durden";
        bool isPC = true;
        bool isDifficult = false;
        void clearBoard(Board& board);
        void randomizeFirstPlayer();
        bool place(Board& board, Coordinates& obj,Dictionary& dict, bool isP2);
        Coordinates evaluateInput(string inp);
        bool generateMove(Board& board, Dictionary& dict, string& res, int& misx, int& misy, char& misch);
        bool generateMove(Board& board, Dictionary& dict);
        int score(bool isUser,Dictionary& dict);
        void centerWord(Board& board, string word);
        void saveGame(Board& board, Dictionary& dict);
        vector<Gamedata> getLeaderboards();
        Gamedata getLeaderboards(string name);
};

#endif