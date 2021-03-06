#include"board.h"
#include<limits.h>
#ifndef STATE_H_
#define STATE_H_

class State
{
public:

    State(){};
    ~State(){};
    State(const Board &board){b=board;}

    Board& getBoard() {return b;}
    void setBoard(const Board &board) {b = board;}
    Position getPosition ()const { return pos;}
    void setPosition(const Position &p) {pos = p;}

    int getPlayerNo()const {return pyNo;}
    void setPlayerNo(const int &playerNo){pyNo=playerNo;}
    int getOpponent()const {return 3-pyNo;}
    int getVisitCount()const{return visitCount;}
    void setVisitCount(const int &vc){visitCount = vc;}
    double getWinScore()const{return winScore;}
    void setWinScore(const double &ws){winScore = ws;}

    void incrementVisit();
    void addScore(const double &score);
    void randomPlay();
    void togglePlayer();
private:
    Board b;
    int pyNo;
    int visitCount=0;
    int winScore=0;
    Position pos;

};
#endif // STATE_H_
