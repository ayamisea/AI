#include"game.h"
int main()
{
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
    if(game.getFirst()=="y")
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
        game.setMoveRecord(pos,game.getP1No());
    }
    else
    {
        srand(time(NULL));
        game.setP1No(rand()%2+1);
    }

    while(!game.End())
    {
        //AI
        game.AIstrategy();
        if(game.End())break;
        system("pause");
        system("cls");

        //Player
        do
        {
            game.getBoard().Display();
            game.showColor();
            game.ShowRemainBrick();

            std::cout<<"What the brick do you want to take away[row,col]?";
            scanf("%d %d",&pos.row,&pos.col);
        }
        while(!game.getBoard().performMove(pos,game.getP1No()));

        game.setMoveRecord(pos,game.getP1No());
    }
    system("pause");
    system("cls");

    return 0;
}
