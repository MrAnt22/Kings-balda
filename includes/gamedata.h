#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "control.h"
#include "board.h"

#include <unordered_set>
#include <string>

using namespace std;

class Board;

struct Gamedata {
    public:
    Board board;
    int p1score;
    int p2score;
    bool isPC;
    string p1name;
    string p2name;
    bool ignore = false;
    Gamedata(Board& brd,string p1n, string p2n, int p1s, int p2s, bool iscomputer) {
        for(int i = 0; i < brd.size; i++) {
            for(int j = 0; j < brd.size; j++) {
                board.field[i][j] = brd.field[i][j];
            }
        }
        for(int i = 0; i < brd.size; i++) {
            for(int j = 0; j < brd.size; j++) {
                board.isP1[i][j] = brd.isP1[i][j];
            }
        }

        p1name = p1n;
        p2name = p2n;
        p1score = p1s;
        p2score = p2s;
        isPC = iscomputer;
        ignore = false;
    }
    Gamedata() {
        isPC = true;
        p1score = false;
        p2score = false;
        p1name = "";
        p2name = "";
        ignore = false;
    }
};

#endif