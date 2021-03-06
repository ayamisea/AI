#include"board.h"

void Board::Display()
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
                if(randColor)SetColor(12,0); //Red
                else SetColor(9,0); //Blue
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
    std::cout<<"\n";
}

bool Board::Create(const int s)
{
    size = s;
    try
    {
        board.resize(s,std::vector<int>(s,0));
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        return false;
    }

    srand(time(NULL));
    randColor=rand()%2;
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

bool Board::performMove(const Position &p,int pyNo)
{
    int r = p.row-1;
    int c = p.col-1;

    if(!PositionExist(r,c)) return false;
    if(board[r][c]==0 || board[r][c]!=pyNo) return false;

    board[r][c]=0;

    int cut=0;
    if(PositionExist(r-1,c)&&board[r-1][c]!=0&&!Stay(r-1,c)) //Check Up
    {
        board[r-1][c]=0;
        cut++;
    }
    if(PositionExist(r+1,c)&&board[r+1][c]!=0&&!Stay(r+1,c)) //Check Down
    {
        board[r+1][c]=0;
        cut++;
    }
    if(PositionExist(r,c-1)&&board[r][c-1]!=0&&!Stay(r,c-1)) //Check Left
    {
        board[r][c-1]=0;
        cut++;
    }
    if(PositionExist(r,c+1)&&board[r][c+1]!=0&&!Stay(r,c+1)) //Check Right
    {
        board[r][c+1]=0;
        cut++;
    }

    return true;
}

int Board::getNumRemainBricks(int pyNo)const
{
    int counter=0;
    for(int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            if(board[i][j]==pyNo) counter++;
        }
    }
    return counter;
}

std::vector<Position> Board::getRemainBricks(int pyNo)const
{
    std::vector<Position> buffer;
    for(int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            if(board[i][j]==pyNo)
            {
                Position p;
                p.row = i+1;
                p.col = j+1;
                buffer.push_back(p);
            }
        }
    }
    return buffer;
}

int Board::checkStatus(int pyNo) const
{
    int opponent = 3-pyNo;
    int pBricks = getNumRemainBricks(pyNo);
    int oBricks = getNumRemainBricks(opponent);
    if(pBricks!=0 && oBricks!=0) return IN_PROGRESS;
    if(pBricks == 0 && oBricks == 0) return DRAW;
    else if(pBricks == 0) return WIN;
    else return LOSE;
}
