#include"player.h"
#include<limits.h>
#include <stdlib.h>
#include <time.h>
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
    void ShowRemainBrick();
    void AIstrategy();
    std::string first;
    Board getBoard()const;
    void setP1No(int no);
    int getP1No()const;
private:
    Board b;
    Player p1;
    Player p2; //ai

};
#endif // GAME_H_
