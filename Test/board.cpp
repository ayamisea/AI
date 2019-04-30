#include"board.h"

void Board::print()
{
    for(int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            if(board[i][j]==1) std::cout<<"*";
            else std::cout<<"-";
        }
        std::cout<<"\n";
    }
}

bool Board::Create()
{
    board = new int*[size];
    for(int i=0;i<size;++i)
    {
        board[i]=new int[size];
    }

    if(board)
    {
        for(int i=0;i<size;++i)
        {
            for(int j=0;j<size;++j)
            {
               board[i][j]=1;
            }
        }
        return true;
    }
    return false;
}

void Board::Delete()
{
    for(int i=0; i<size;++i)
    {
        delete [] board[i];
    }
    delete [] board;
    board=NULL;
}
