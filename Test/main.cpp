#include"game.h"
#include "mcts.h"

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

        do
        {
            std::cout<<"What the brick do you want to take away[row,col]?";
            scanf("%d %d",&pos.row,&pos.col);

        }
        while(!game.getBoard().PositionExist(pos.row-1,pos.col-1));

        game.setP1No(game.getBoard().board[pos.row-1][pos.col-1]);
        game.getBoard().performMove(pos,game.getP1No());
        std::cout<<"Attack!!\n";
        game.setMoveRecord(pos,game.getP1No());
    }
    else
    {
        srand(time(NULL));
        game.setP1No(rand()%2+1);
    }

    while(!game.End())
    {
        game.AIstrategy();

        if(game.End())break;
        do
        {
            system("pause");
            system("cls");
            game.getBoard().Display();
            game.showColor();
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
