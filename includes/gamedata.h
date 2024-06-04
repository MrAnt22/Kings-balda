#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "control.h"
#include "board.h"

#include <set>
#include <string>

class Board;

struct Gamedata {
    public:
    Board board;
    int p1score = 0;
    int p2score = 0;
    set<string> p1words;
    set<string> p2words;
    string p1name;
    string p2name;
};

#endif