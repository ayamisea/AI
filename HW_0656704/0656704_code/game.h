#include"board.h"
#include"mcts.h"
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
    void showMoveRecord();
    void showColor();

    void setP1No(int no);
    void setMoveRecord(const Position &p,int pyNo);

    Board& getBoard(){return b;}
    std::string getFirst()const {return first;}
    int getP1No()const{return p1No;};

private:
    Board b;
    MCTS m;
    int p1No=1;
    int p2No=2; //AI
    std::vector<Position> p1moveRecord;
    std::vector<Position> p2moveRecord;
    std::string first;
};
#endif // GAME_H_
