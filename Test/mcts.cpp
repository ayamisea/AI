#include"mcts.h"

int MCTS::getMillisForCurrentLevel()
{
    return 2 *(level -1)+1;
}

Position MCTS::findNextMove(const Board &b,int pyNo)
{
    long long start_ = currentTimeMillis();
    long long end_ = start_ + 1200 * getMillisForCurrentLevel();
    //std::cout<<start_<<" "<<end_;

    opponent = 3 - pyNo;

    Tree tree;
    //Node rootNode = tree.getRoot();
    tree.getRoot().parenet = NULL;
    tree.getRoot().state.setBoard(b);
    tree.getRoot().state.setPlayerNo(opponent);

    //while(currentTimeMillis() < end_)
    //int counter=0;
    while(currentTimeMillis() < end_)
    {
        //Section
        Node* promisingNode = selectPromisingNode(tree.getRoot());

        /*
        std::cout<<"Promising Node:\n";
        promisingNode->state.getBoard().Display();
        std::cout<<"================================\n";
        */

        //Expansion
        if(promisingNode->state.getBoard().checkStatus(pyNo)==promisingNode->state.getBoard().IN_PROGRESS)
        {

            expandNode(promisingNode);
        }

        /*
        for(auto const& n :promisingNode->childArray)
        {
            std::cout<<n->state.getPosition().row<<" "<<n->state.getPosition().col<<"\n";
            n->state.getBoard().Display();
        }
        */

        //Simulation
        Node* nodeToExplore = promisingNode;
        if(promisingNode->childArray.size() > 0)
        {
            nodeToExplore = tree.getRandomChildNode(promisingNode);
        }

        /*
        std::cout<<"Node to explore: "<<nodeToExplore->state.getPosition().row<<","<<nodeToExplore->state.getPosition().col<<"\n";
        nodeToExplore->state.getBoard().Display();
        std::cout<<"-----------------------\n";
        */

        int playoutResult = simulateRandomPlayout(nodeToExplore);

        /*
        if(playoutResult==opponent) std::cout<<"We Lose...\n";
        if(playoutResult==0) std::cout<<"DRAW\n";
        if(playoutResult==pyNo) std::cout<<"We Win.\n";
        */


        //Update
        backPropogation(nodeToExplore,playoutResult);


        std::cout<<"tree root Visit:"<<tree.getRoot().state.getVisitCount()<<"\n\n";
        while(nodeToExplore != NULL)
        {
           std::cout<<"<"<<nodeToExplore->state.getPosition().row<<","<<nodeToExplore->state.getPosition().col<<">\n";
           std::cout<<"Visit:"<<nodeToExplore->state.getVisitCount()<<"\n";
           std::cout<<"winScore:"<<nodeToExplore->state.getWinScore()<<"\n";
           nodeToExplore = nodeToExplore->parenet;
        }

        //counter++;


    }


    Position winPosition = tree.getChildWithMaxScore(tree.getRoot())->state.getPosition();
    //tree.setRoot(winnerNode);

    std::cout<<"-----"<<tree.getRoot().state.getVisitCount();

    /*
    std::cout<<"Winner:\n";
    winnerNode->state.getBoard().Display();
    std::cout<<winnerNode->state.getPosition().row<<" "<<winnerNode->state.getPosition().col<<"\n";
    */

    return winPosition;
}

Node* MCTS::selectPromisingNode(Node &n)
{
    Node* node = &n;
    //std::cout<<node->state.getVisitCount()<<" "<<node->state.getWinScore()<<"+++\n";
    while(node->childArray.size() != 0)
    {
        node = findBestNodeWithUCT(node);
        //std::cout<<node->state.getVisitCount()<<" "<<node->state.getWinScore()<<"****\n";
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
    int opPyNo = tempState.getOpponent();
    int boardStatus = tempState.getBoard().checkStatus(pyNo);

    tempNode->state.getBoard().Display();
    std::cout<<boardStatus<<" "<<pyNo<<" "<<opponent<<"\n";

    int win = tempState.getBoard().WIN;
    int in_progress=tempState.getBoard().IN_PROGRESS;
    int draw = tempState.getBoard().DRAW;

    if( (boardStatus == win && pyNo==opponent))
    {
        node->parenet->state.setWinScore((double)INT_MIN);

        std::cout<<"!!!";
        tempState.getBoard().Display();
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
        //tempState.getBoard().Display();
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
    std::cout<<"find UCT=============\n";
    for(auto & node: n->childArray)
    {
        double uct=uctValue(parentVisit,node->state.getWinScore(),node->state.getVisitCount());

        std::cout<<"<"<<node->state.getPosition().row<<", "<<node->state.getPosition().col<<" >"<<uct;

        if (uct>max_UCT)
        {
            maxNode = node;
            max_UCT = uct;
            std::cout<<" <-- max";
        }
        std::cout<<"\n";

    }
    return maxNode;
}
double MCTS::uctValue(int totalVisit,double nodeWinScore,int nodeVisit)
{
    double c = 1.14;
    if(nodeVisit==0) return (double)INT_MAX;
    return (nodeWinScore /(double) nodeVisit)+ c*sqrt(log(totalVisit)/(double)nodeVisit);
}
