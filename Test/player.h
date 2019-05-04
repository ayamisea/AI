#include<iostream>
#include"board.h"
#include<vector>
#ifndef PLAYER_H_
#define PLAYER_H_


class Player
{
public:
    Player(){};
    ~Player(){};
    void SetNo (int no);
    int remaining_bricks = 0;
    int No = 0;
    std::vector<Position> moveRecord;
};
#endif // PLAYER_H_
