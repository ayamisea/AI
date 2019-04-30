#include<iostream>
#include"board.h"
#ifndef PLAYER_H_
#define PLAYER_H_
class Player
{
public:
    Player(){};
    ~Player(){};
    void Setting (int bricks_,int state_);
    int remaining_bricks = 0;
    int state = 0;
};
#endif // PLAYER_H_
