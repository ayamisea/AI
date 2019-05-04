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
            if(board[i][j]==1)
            {
                if(randColor)SetColor(12,0);
                else SetColor(9,0);
            }
            else if(board[i][j]==2)
            {
                if(!randColor) SetColor(12,0);
                else SetColor(9,0);
            }
            else SetColor(0,0);
            std::cout<<std::setw(4)<<"*";
        }
        std::cout<<"\n";
    }
    SetColor(15,0);
}

bool Board::Create()
{
    try
    {
        board = new int*[size];
        for(int i=0;i<size;++i)  board[i]=new int[size];
    }
    catch(std::bad_alloc) {return false;}

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

bool Board::PositionExist(int r,int c)
{
    if(r<0||r>=size||c<0||c>=size) return false;
    return true;
}

bool Board::Stay(int r, int c)
{

    int zero_counter = 0;
    if(PositionExist(r-1,c)&&board[r-1][c]==0) zero_counter++;//Up
    if(PositionExist(r+1,c)&&board[r+1][c]==0) zero_counter++;//Down
    if(PositionExist(r,c-1)&&board[r][c-1]==0) zero_counter++;//Left
    if(PositionExist(r,c+1)&&board[r][c+1]==0) zero_counter++;//Right

    if(zero_counter>=2) return false;
    return true;
}
