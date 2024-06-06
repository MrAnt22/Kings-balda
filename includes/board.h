#ifndef BOARD_H
#define BOARD_H
#define SIZE 5

#include "coordinates.h"

class View;
class Control;

struct Board{
    char field[SIZE][SIZE] = {0};
    int isP1[SIZE][SIZE] = {0};
    Coordinates p1Move;
    Coordinates p2Move;
    int size = SIZE;
public:
    friend class View;
    friend class Control;
};

#endif