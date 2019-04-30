#include "game.h"
#include<time.h>
int main()
{
    int n =1;
    Game game;
    if(!game.Initialize())
    {
        std::cout<<"Error ...";
        return 0;
    }
    else std::cout<<"Start the game.\n";
    std::cin.sync();
    system("pause");
    system("cls");

    while(!game.End())
    {
        game.Display();
        game.ShowRemainBrick();

        int row=0;
        int col=0;

        std::cout<<"What the brick do you want to take away[row,col]?";
        scanf("%d %d",&row,&col);
        if(game.Attack(row,col)) std::cout<<"Attack!!\n";
        else std::cout<<"Cannot attack!!\n";

        std::cin.sync();
        system("pause");
        system("cls");
    }

    return 0;
}
