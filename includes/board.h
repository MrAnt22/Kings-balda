#ifndef BOARD_H
#define BOARD_H
#define SIZE 5

class View;
class Control;

struct Board{
    char field[SIZE][SIZE];
    int size = SIZE;
public:
    friend class View;
    friend class Control;
};

#endif