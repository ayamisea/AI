#include"board.h"
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
    void setMoveRecord(const Position &p,int pyNo);
    void showMoveRecord();
    void showColor();
private:
    Board b;
    int p1No=0;
    int p2No=0; //ai
    std::vector<Position> p1moveRecord;
    std::vector<Position> p2moveRecord;

};
#endif // GAME_H_
