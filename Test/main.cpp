#include "game.h"

#include"tree.h"
#include<time.h>
int main()
{

    //Test

    Node node;
    node.id=10;
    Node p;
    p.id=11;
    Node c;
    c.id = 12;
    Tree t;

    t.addChild(node,c);
    node.childArray[0].id = 200;
    std::cout<<node.childArray[0].parenet<<" ";
    std::cout<<&node<<" ";

    t.setRoot(node);
    std::cout<<&t.root.childArray[0].parenet<<" ";


    return 0;
    //


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
