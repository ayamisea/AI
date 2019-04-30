#include"game.h"
bool Game::Initialize()
{
    while(true)
    {
        std::cout<<"Please input the size of board:";
        std::cin>>b.size;
        if(b.size<0 || b.size>=INT_MAX) return false; //overflow checking
        if(b.size%2)std::cout<<"Size cannot be odd.\n";
        else break;
    }

    if(!b.Create()) return false; //Board -> Insufficient memory!
    return true;
}

void Game::Display()
{
    b.print();

}
void Game::End()
{
    b.Delete();
}
