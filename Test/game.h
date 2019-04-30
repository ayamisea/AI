#include"board.h"
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
    void End();
private:
    Board b;
    Player p1;
    Player p2; //ai
};
#endif // GAME_H_