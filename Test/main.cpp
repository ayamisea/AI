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
    system("pause");
    system("cls");
    game.Display();
    game.End();

    return 0;
}
