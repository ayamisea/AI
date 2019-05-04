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
    p1.Setting(bricks);
    p2.Setting(bricks);
    std::cout<<"Do you want to play first [y/n]?";
    std::cin>>first;
    srand(time(NULL));
    b.randColor = rand()%2;

    if(!b.Create()) return false; //Board -> Insufficient memory!
    return true;
}

void Game::Display()
{
    b.Print();
    std::cout<<"\n"<<"You:red  PC:green\n\n";

}
bool Game::End()
{
    if(p1.remaining_bricks!=0 && p2.remaining_bricks!=0) return false;
    b.Delete();
    if(p1.remaining_bricks==0&&p2.remaining_bricks==0) std::cout<<"The game ended in a draw.\n";
    else if(p1.remaining_bricks==0) std::cout<<"You win!!\n";
    else std::cout<<"You lose~~\n";
    return true;
}

bool Game::Attack(int row,int col,int pyNo)
{
    int r = row-1;
    int c = col-1;

    if(!b.PositionExist(r,c)) return false;
    if(b.board[r][c]==0 || b.board[r][c]!=pyNo) return false;

    if(b.board[r][c]==p1.No) p1.remaining_bricks--;
    else p2.remaining_bricks--;
    int turn = b.board[r][c];
    b.board[r][c]=0;

    int cut=0;
    if(b.PositionExist(r-1,c)&&b.board[r-1][c]!=0&&!b.Stay(r-1,c)) //Check Up
    {
        b.board[r-1][c]=0;
        cut++;
    }
    if(b.PositionExist(r+1,c)&&b.board[r+1][c]!=0&&!b.Stay(r+1,c)) //Check Down
    {
        b.board[r+1][c]=0;
        cut++;
    }
    if(b.PositionExist(r,c-1)&&b.board[r][c-1]!=0&&!b.Stay(r,c-1)) //Check Left
    {
        b.board[r][c-1]=0;
        cut++;
    }
    if(b.PositionExist(r,c+1)&&b.board[r][c+1]!=0&&!b.Stay(r,c+1)) //Check Right
    {
        b.board[r][c+1]=0;
        cut++;
    }

    if(turn==p1.No) p2.remaining_bricks-=cut;
    else p1.remaining_bricks-=cut;

    return true;
}

void Game::ShowRemainBrick()
{
    std::cout<<"Remaining Bricks:"<<" You:"<<p1.remaining_bricks<<", AI:"<<p2.remaining_bricks<<"\n\n";
}

void Game::AIstrategy()
{

}

Board Game::getBoard()const
{
    return b;
}
void Game::setP1No(int no)
{
    p1.No=no;
    p2.No=3 - no;
}
int Game::getP1No()const
{
    return p1.No;
}
