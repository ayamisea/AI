#include"board.h"

void Board::Print()
{
    SetColor(15,0);
    for(int i=0;i<size+1;++i) std::cout<<std::setw(4)<<i;
    std::cout<<"\n";
    for(int i=0;i<size;++i)
    {
        SetColor(15,0);
        std::cout<<std::setw(4)<<i+1;
        for(int j=0;j<size;++j)
        {
            if(board[i][j]==1) SetColor(12,0);
            else SetColor(10,0);
            std::cout<<std::setw(4)<<"*";
        }
        std::cout<<"\n";
    }
    SetColor(15,0);
}

bool Board::Create()
{
    board = new int*[size];
    for(int i=0;i<size;++i)  board[i]=new int[size];

    if(board)
    {
        for(int i=0;i<size;++i)
        {
            for(int j=0;j<size;++j)
            {
                if ((i+j)%2==0) board[i][j]=1;
                else board[i][j]=2;
            }
        }
        return true;
    }
    return false;
}

void Board::Delete()
{
    for(int i=0; i<size;++i) delete [] board[i];
    delete [] board;
    board=NULL;
}

void Board::SetColor(int font,int background)
{
    unsigned short color=font+16*background;
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}
