#include"game.h"
bool Game::Initialize()
{
    int s;
    while(true)
    {

        std::cout<<"Please input the size of board. [n by n]:";
        std::cin>>s;
        if(s<0 || s>=INT_MAX) return false;
        if(s%2)std::cout<<"Size cannot be odd.\n";
        else break;
    }

    std::cout<<"Do you want to play first [y/n]?";
    std::cin>>first;

    //Board initialize
    if(!b.Create(s)) return false;
    return true;
}

bool Game::End()
{
    if(b.checkStatus(p1No)==b.IN_PROGRESS) return false;

    system("pause");
    system("cls");

    b.Display();

    if(b.checkStatus(p1No)==b.DRAW) std::cout<<"The game ended in a draw.\n";
    else if(b.checkStatus(p1No)==b.WIN) std::cout<<"You win!!\n";
    else std::cout<<"You lose~~\n";
    showMoveRecord();

    return true;
}

void Game::ShowRemainBrick()
{
    std::cout<<"Remaining Bricks:"<<" You:"<<b.getNumRemainBricks(p1No)<<", AI:"<<b.getNumRemainBricks(p2No)<<"\n\n";
}

void Game::AIstrategy()
{
    Position pos;

    //MCTS
    pos = m.findNextMove(b,p2No);
    b.performMove(pos,p2No);
    setMoveRecord(pos,p2No);

    std::cout<<"AI Attack!! <"<<pos.row<<","<<pos.col<<">\n";

}

void Game::setP1No(int no)
{
    p1No = no;
    p2No = 3 - no;
}
void Game::setMoveRecord(const Position &p,int pyNo)
{
    if(pyNo==p1No) p1moveRecord.push_back(p);
    else if(pyNo==p2No) p2moveRecord.push_back(p);
}

void Game::showMoveRecord()
{
    std::cout<<"Your move: ";
    for(auto &i : p1moveRecord) std::cout <<"<"<<i.row<<","<<i.col<<"> ";
    std::cout<<"\nAI move: ";
    for(auto &i : p2moveRecord) std::cout <<"<"<<i.row<<","<<i.col<<"> ";
    std::cout<<"\n";
}

void Game::showColor()
{
    int color = b.getRandColor();
    std::cout<<"You:";
    if( (p1No==1 && color ) || (p1No==2 &&!color)) std::cout<<"Red "<<"AI:Blue"<<std::endl;
    else std::cout<<"Blue "<<"AI:Red"<<std::endl;
}
