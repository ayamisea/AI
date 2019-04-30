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
    p1.SetRemBrick(bricks);
    p2.SetRemBrick(bricks);
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

    return true;
}

bool Game::Attack(int row,int col)
{
    int r = row-1;
    int c = col-1;
    if(r<0||r>=b.size||c<0||c>=b.size) return false;
    return true;
}
