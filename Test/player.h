#include<iostream>
#include"board.h"
#include<vector>
#ifndef PLAYER_H_
#define PLAYER_H_

struct Position
{
    int row;
    int col;
};
class Player
{
public:
    Player(){};
    ~Player(){};
    void Setting (int bricks_);
    int remaining_bricks = 0;
    int No = 0;
    std::vector<Position> moveRecord;
};
#endif // PLAYER_H_
