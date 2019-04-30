#include"player.h"
#include<limits.h>
#ifndef GAME_H_
#define GAME_H_
class Game
{
public:
    Game(){};
    ~Game(){};
    bool Initialize();
    void Display();
    bool End();
    bool Attack(int row,int col);
    void ShowRemainBrick();
    void AIstrategy();
private:
    Board b;
    Player p1;
    Player p2; //ai

};
#endif // GAME_H_
