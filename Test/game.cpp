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
    p1.SetNo(1);
    p2.SetNo(2);
    std::cout<<"Do you want to play first [y/n]?";
    std::cin>>first;
    srand(time(NULL));
    b.randColor = rand()%2;

    if(!b.Create()) return false; //Board -> Insufficient memory!
    return true;
}

bool Game::End()
{
    if(b.getRemainBricks(p1.No)!=0 && b.getRemainBricks(p2.No)!=0) return false;
    b.Delete();
    if(b.getRemainBricks(p1.No)==0&&b.getRemainBricks(p2.No)==0) std::cout<<"The game ended in a draw.\n";
    else if(b.getRemainBricks(p1.No)==0) std::cout<<"You win!!\n";
    else std::cout<<"You lose~~\n";
    return true;
}



void Game::ShowRemainBrick()
{
    std::cout<<"Remaining Bricks:"<<" You:"<<b.getRemainBricks(p1.No)<<", AI:"<<b.getRemainBricks(p2.No)<<"\n\n";
}

void Game::AIstrategy()
{
    Position pos;
    do
    {
        system("pause");
        system("cls");
        b.Display();
        ShowRemainBrick();

        std::cout<<"AI attack [row,col]?";
        scanf("%d %d",&pos.row,&pos.col);

    }
    while(!getBoard().performMove(pos,p2.No));
    std::cout<<"AI Attack!!\n";

}

Board Game::getBoard()const
{
    return b;
}
void Game::setP1No(int no)
{
    p1.SetNo(no);
    p2.SetNo(3 - no);
}
int Game::getP1No()const
{
    return p1.No;
}
