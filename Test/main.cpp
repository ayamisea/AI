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


    Position pos;
    if(game.first=="y")
    {
        game.getBoard().Display();
        game.ShowRemainBrick();

        std::cout<<"What the brick do you want to take away[row,col]?";
        scanf("%d %d",&pos.row,&pos.col);

        while(!game.getBoard().PositionExist(pos.row,pos.col))
        {
            std::cout<<"Over Board!\n";
            std::cout<<"What the brick do you want to take away[row,col]?";
            scanf("%d %d",&pos.row,&pos.col);
        }
        game.setP1No(game.getBoard().board[pos.row][pos.col]);
        if(game.getBoard().performMove(pos,game.getP1No()))
        {
            std::cout<<"Attack!!\n";
            game.setMoveRecord(pos,game.getP1No());
        }
        else
        {
            std::cout<<"Cannot attack!!\n";
            return 0;
        }
    }
    else
    {
        srand(time(NULL));
        game.setP1No(rand()%2+1);
    }




    while(!game.End())
    {
        game.AIstrategy();
        std::cin.sync();

        do
        {
            system("pause");
            system("cls");
            game.getBoard().Display();
            game.ShowRemainBrick();

            std::cout<<"What the brick do you want to take away[row,col]?";
            scanf("%d %d",&pos.row,&pos.col);
        }
        while(!game.getBoard().performMove(pos,game.getP1No()));

        std::cout<<"Attack!!\n";
        game.setMoveRecord(pos,game.getP1No());
        game.showMoveRecord();

    }

    return 0;
}
