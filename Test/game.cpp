#include"game.h"
bool Game::Initialize()
{
    while(true)
    {
        std::cout<<"Please input the size of board. [n by n]:";
        std::cin>>b.size;
        if(b.size<0 || b.size>=INT_MAX) return false; //overflow checking
        if(b.size%2)std::cout<<"Size cannot be odd.\n";
        else break;
    }

    int bricks = b.size*b.size/2;
    p1No = 1;
    p2No = 2;
    std::cout<<"Do you want to play first [y/n]?";
    std::cin>>first;
    srand(time(NULL));
    b.setRandColor(rand()%2);
    b.Create();

    return true;
}

bool Game::End()
{
    if(b.checkStatus(p1No)==b.IN_PROGRESS) return false;

    if(b.checkStatus(p1No)==b.DRAW) std::cout<<"The game ended in a draw.\n";
    else if(b.checkStatus(p1No)==b.WIN) std::cout<<"You win!!\n";
    else std::cout<<"You lose~~\n";

    // b.Delete();
    return true;
}



void Game::ShowRemainBrick()
{
    std::cout<<"Remaining Bricks:"<<" You:"<<b.getNumRemainBricks(p1No)<<", AI:"<<b.getNumRemainBricks(p2No)<<"\n\n";
}

void Game::AIstrategy()
{
    Position pos;

    /***Case input
    do
    {
        system("pause");
        system("cls");
        b.Display();
        ShowRemainBrick();

        std::cout<<"AI attack [row,col]?";
        scanf("%d %d",&pos.row,&pos.col);

    }
    while(!getBoard().performMove(pos,p2No));

    ***/
    //uniform cost


    //MCTS

    m.findNextMove(b,p2No);



    std::cout<<"AI Attack!!\n";
    //setMoveRecord(pos,p2No);

}

Board& Game::getBoard()
{
    return b;
}
void Game::setP1No(int no)
{
    p1No = no;
    p2No = 3 - no;
}
int Game::getP1No()const
{
    return p1No;
}
void Game::setMoveRecord(const Position &p,int pyNo)
{
    if(pyNo==p1No) p1moveRecord.push_back(p);
    else if(pyNo==p2No) p2moveRecord.push_back(p);
}

void Game::showMoveRecord()
{
    std::cout<<"Your move:";
    for(auto &i : p1moveRecord) std::cout <<"<"<<i.row<<","<<i.col<<"> ";
    std::cout<<"\nAI move:";
    for(auto &i : p2moveRecord) std::cout <<"<"<<i.row<<","<<i.col<<"> ";
    std::cout<<"\n";
}

void Game::showColor()
{
    int color = b.getRandColor();
    std::cout<<"You:";
    if( (p1No==1 && color ) || (p1No==2 &&!color)) std::cout<<"Red "<<"AI:Blue\n"<<std::endl;
    else std::cout<<"Blue "<<"AI:Red\n"<<std::endl;

}
