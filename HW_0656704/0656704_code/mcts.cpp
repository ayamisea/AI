#include"mcts.h"

int MCTS::getMillisForCurrentLevel()
{
    return 2 *(level -1)+1;
}

Position MCTS::findNextMove(const Board &b,int pyNo)
{
    long long start_ = currentTimeMillis();
    long long end_ = start_ + 1200 * getMillisForCurrentLevel();

    opponent = 3 - pyNo;

    Tree* tree = new Tree();
    tree->getRoot().parenet = NULL;
    tree->getRoot().state.setBoard(b);
    tree->getRoot().state.setPlayerNo(opponent);

    while(currentTimeMillis() < end_)
    {
        //Section
        Node* promisingNode = selectPromisingNode(tree->getRoot());

        //Expansion
        if(promisingNode->state.getBoard().checkStatus(pyNo)==promisingNode->state.getBoard().IN_PROGRESS)
        {
            expandNode(promisingNode);
        }

        //Simulation
        Node* nodeToExplore = promisingNode;
        if(promisingNode->childArray.size() > 0)
        {
            nodeToExplore = tree->getRandomChildNode(promisingNode);
        }

        int playoutResult = simulateRandomPlayout(nodeToExplore);

        //Back propagation
        backPropogation(nodeToExplore,playoutResult);

    }

    Position winPosition = tree->getChildWithMaxScore(tree->getRoot())->state.getPosition();
    delete tree;
    tree = NULL;

    return winPosition;
}

Node* MCTS::selectPromisingNode(Node &n)
{
    Node* node = &n;
    while(node->childArray.size() != 0)
    {
        node = findBestNodeWithUCT(node);
    }

    return node;
}

void MCTS::expandNode(Node* node)
{
    int No=node->state.getOpponent();
    std::vector<State> possibleStates;
    std::vector<Position> availavlePositions = node->state.getBoard().getRemainBricks(No);

    //setAllPossibleStates
    Board b=node->state.getBoard();
    for(auto const& pos:availavlePositions)
    {
        State newState;
        newState.setBoard(b);
        newState.setPlayerNo(No);
        newState.setPosition(pos);
        newState.getBoard().performMove(pos,No);
        possibleStates.push_back(newState);
    }

    //expandNodes
    for(auto const& s:possibleStates)
    {
        Node* newNode = new Node{};
        newNode->state=s;
        newNode->parenet=node;
        newNode->state.setPlayerNo(No);
        node->childArray.push_back(newNode);
    }

}
void MCTS::backPropogation(Node* nodeToExplore,int pyNo)
{
    Node *tempNode = nodeToExplore;
    while(tempNode != NULL)
    {
        tempNode->state.incrementVisit();
        if(tempNode->state.getPlayerNo() == pyNo)
        {
            tempNode->state.addScore(WIN_SCORE);
        }
        tempNode = tempNode->parenet;
    }
}
int MCTS::simulateRandomPlayout(Node* node)
{
    Node* tempNode = (new Node(*node));
    State tempState = tempNode->state;
    int pyNo = tempState.getPlayerNo();
    int boardStatus = tempState.getBoard().checkStatus(pyNo);
    int win = tempState.getBoard().WIN;
    int in_progress=tempState.getBoard().IN_PROGRESS;
    int draw = tempState.getBoard().DRAW;
    int lose = tempState.getBoard().LOSE;

    if(boardStatus == win && pyNo==opponent)
    {
        node->parenet->state.setWinScore((double)INT_MIN);
        delete tempNode;
        tempNode = NULL;
        return opponent;
    }
    else if( boardStatus == lose && pyNo==(3-opponent))
    {
        node->state.setWinScore((double)INT_MIN);
        delete tempNode;
        tempNode = NULL;
        return opponent;
    }
    while(boardStatus == in_progress)
    {
        tempState.togglePlayer();
        tempState.randomPlay();
        int nowPyNo = tempState.getPlayerNo();
        boardStatus = tempState.getBoard().checkStatus(nowPyNo);
    }

    delete tempNode;
    tempNode = NULL;

    if(boardStatus == draw) return draw;
    else if(boardStatus == win && tempState.getPlayerNo()==opponent) return opponent;
    return 3 - opponent;
}

long long MCTS::currentTimeMillis()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    long long t = tv.tv_sec;
    t *= 1000;
    t += tv.tv_usec/1000;
    return t;
}

Node* MCTS::findBestNodeWithUCT( Node* n)
{
    int parentVisit = n->state.getVisitCount();

    Node* maxNode = NULL;
    double max_UCT=(double)INT_MIN;
    for(auto & node: n->childArray)
    {
        double uct=uctValue(parentVisit,node->state.getWinScore(),node->state.getVisitCount());
        if (uct>max_UCT)
        {
            maxNode = node;
            max_UCT = uct;
        }
    }
    return maxNode;
}
double MCTS::uctValue(int totalVisit,double nodeWinScore,int nodeVisit)
{
    double c = 1.14;
    if(nodeVisit==0) return (double)INT_MAX;
    return (nodeWinScore /(double) nodeVisit)+ c*sqrt(log(totalVisit)/(double)nodeVisit);
}
