#include<iostream>
#ifndef PLAYER_H_
#define PLAYER_H_
class Player
{
public:
    Player(){};
    ~Player(){};
    void SetRemBrick(int num);
    int remaining_bricks = 0;
};
#endif // PLAYER_H_
