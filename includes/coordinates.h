#ifndef COORDINATES_H
#define COORDINATES_H
#include "move.h"

struct Coordinates{
public:
    friend class View;
    friend class Control;
    int x;
    int y;
    bool ignore = false;
    char symbol;
    Move move[10] = {N,N,N,N,N,N,N,N,N,N};
};

#endif