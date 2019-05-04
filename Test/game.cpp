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
    b.randColor = rand()%2;

    if(!b.Create()) return false; //Board -> Insufficient memory!
    return true;
}

bool Game::End()
{
    if(b.getRemainBricks(p1No)!=0 && b.getRemainBricks(p2No)!=0) return false;
    b.Delete();
    if(b.getRemainBricks(p1No)==0&&b.getRemainBricks(p2No)==0) std::cout<<"The game ended in a draw.\n";
    else if(b.getRemainBricks(p1No)==0) std::cout<<"You win!!\n";
    else std::cout<<"You lose~~\n";
    return true;
}



void Game::ShowRemainBrick()
{
    std::cout<<"Remaining Bricks:"<<" You:"<<b.getRemainBricks(p1No)<<", AI:"<<b.getRemainBricks(p2No)<<"\n\n";
}

void Game::AIstrategy()
{
    Position pos;

    //Case input
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

    //uniform cost


    std::cout<<"AI Attack!!\n";
    setMoveRecord(pos,p2No);

}

Board Game::getBoard()const
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

