#include"mcts.h"

int MCTS::getMillisForCurrentLevel()
{
    return 2 *(level -1)+1;
}

Board MCTS::findNextMove(const Board &b,int pyNo)
{
    long long start_ = currentTimeMillis();
    long long end_ = start_ + 60 * getMillisForCurrentLevel();
    //std::cout<<start_<<" "<<end_;

    opponent = 3 - pyNo;

    Tree tree;
    //Node rootNode = tree.getRoot();
    tree.getRoot().state.setBoard(b);
    tree.getRoot().state.setPlayerNo(opponent);

    //while(currentTimeMillis() < end_)
    int counter=0;
    while(counter<2)
    {
        //Section

        Node* promisingNode = selectPromisingNode(tree.getRoot());

        //std::cout<<&tree.getRoot()<<" "<<promisingNode;

        //Expansion

        if(promisingNode->state.getBoard().checkStatus(pyNo)==promisingNode->state.getBoard().IN_PROGRESS)
        {

            expandNode(promisingNode);
        }

        for(auto const& n :promisingNode->childArray)
        {
            std::cout<<n->state.getPosition().row<<" "<<n->state.getPosition().col<<"\n";
            n->state.getBoard().Display();
            system("pause");
            system("cls");
        }
/*
        //Simulation
        Node* nodeToExplore;
        if(promisingNode->childArray.size() > 0)
        {
            nodeToExplore = tree.getRandomChildNode(promisingNode);

        }
        int playoutResult = simulateRandomPlayout(nodeToExplore);

        //Update
        backPropogation(nodeToExplore,playoutResult);

        //std::cout<<promisingNode.childArray.size()<<"****";


        system("pause");
        system("cls");
        */

        counter ++;
        }

    /*
    Node* winnerNode = tree.getChildWithMaxScore(tree.getRoot());
    tree.setRoot(winnerNode);

    std::cout<<tree.getRoot().childArray.size()<<"***";
    system("pause");
    system("cls");

    return winnerNode->state.getBoard();
    */

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
    //getAllPossibleStates()
    int No=node->state.getOpponent();
    std::vector<State> possibleStates;
    std::vector<Position> availavlePositions = node->state.getBoard().getRemainBricks(No);

    //Position

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


    //getPossibleStates

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

}
int MCTS::simulateRandomPlayout(Node* node)
{

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

    Node* maxNode;
    double max_UCT=0.0;
    for(auto & node: n->childArray)
    {
        double uct=uctValue(parentVisit,node->state.getWinScore(),node->state.getVisitCount());
        if (uct>=max_UCT) maxNode = node;
    }
    return maxNode;
}
double MCTS::uctValue(int totalVisit,double nodeWinScore,int nodeVisit)
{
    double c = 1.14;
    if(nodeVisit==0) return INT_MAX;
    return (nodeWinScore /(double) nodeVisit)+ c*sqrt(log(totalVisit)/(double)nodeVisit);
}
