#include<iostream>
#include<iomanip>
#include<vector>
#include<windows.h>
#ifndef BOARD_H_
#define BOARD_H_
struct Position
{
    int row=0;
    int col=0;
};
class Board
{
  public:
      Board(){};
      ~Board(){};

      std::vector<std::vector<int>> board;
      bool Create(const int s);
      void Display();
      bool PositionExist(int r,int c);
      bool performMove(const Position &p,int pyNo);
      int checkStatus(int pyNo)const;

      int getNumRemainBricks(int pyNo)const;
      int getSize()const{return size;}
      int getRandColor() const {return randColor;}

      std::vector<Position> getRemainBricks(int pyNo)const;

      enum Status{DRAW,WIN,LOSE,IN_PROGRESS};

  private:
      void SetColor(int font,int background);
      int randColor=1;
      bool Stay(int r,int c);
      int size = 4;
};
#endif // BOARD_H_
