#include"state.h"

void State::incrementVisit()
{
    visitCount++;
}
void State::addScore(const double &score)
{
    if(winScore!=INT_MIN ) winScore += score;
}

void State::randomPlay()
{
    std::vector<Position> availablePositions = b.getRemainBricks(pyNo);
    int totalSize = availablePositions.size();
    srand(time(NULL));
    int selectRandom= rand()%totalSize;
    b.performMove(availablePositions[selectRandom],pyNo);
    pos=availablePositions[selectRandom];

}

void State::togglePlayer()
{
    pyNo = 3 - pyNo;
}
