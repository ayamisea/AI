#include"board.h"
#include"tree.h"
#include<math.h>
#include<sys/time.h>
#include<time.h>
#ifndef MCTS_H_
#define MCTS_H_

class MCTS
{
public:
    int getLevel()const{return level;}
    void setLevel(const int l){level =l;}
    Position findNextMove(const Board &b,int plNo);

private:
    int WIN_SCORE = 10;
    int level = 3;
    int opponent;
    int getMillisForCurrentLevel();
    Node* selectPromisingNode(Node& n);
    void expandNode(Node* node);
    void backPropogation(Node* nodeToExplore,int pyNo);
    int simulateRandomPlayout(Node* node);
    long long currentTimeMillis();

    //UCT
    Node* findBestNodeWithUCT(Node* n);
    double uctValue(int totalVisit,double nodeWinScore,int nodeVisit);
};
#endif // MCTS_H_
