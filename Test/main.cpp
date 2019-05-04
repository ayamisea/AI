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


    int row=0;
    int col=0;
    if(game.first=="y")
    {
        game.Display();
        game.ShowRemainBrick();

        std::cout<<"What the brick do you want to take away[row,col]?";
        scanf("%d %d",&row,&col);

        if(game.getBoard().PositionExist(row,col)) game.setP1No(game.getBoard().board[row][col]);
        if(game.Attack(row,col,game.getP1No())==game.getP1No()) std::cout<<"Attack!!\n";
        else std::cout<<"Cannot attack!!\n";

        system("pause");
        system("cls");
    }
    else game.setP1No(1);


    while(!game.End())
    {
        game.AIstrategy();
        std::cin.sync();

        game.Display();
        game.ShowRemainBrick();

        std::cout<<"What the brick do you want to take away[row,col]?";
        scanf("%d %d",&row,&col);
        if(game.Attack(row,col,game.getP1No())) std::cout<<"Attack!!\n";
        else std::cout<<"Cannot attack!!\n";

        system("pause");
        system("cls");
    }

    return 0;
}
