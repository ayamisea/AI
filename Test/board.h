#include<iostream>
#include<iomanip>
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
      Board(int size){};

      int size = 4;
      int** board = NULL;
      bool Create();
      void Display();
      void Delete();
      bool PositionExist(int r,int c);
      bool Stay(int r,int c);
      int randColor=1;
      bool performMove(const Position &p,int pyNo);
      int getRemainBricks(int pyNo)const;
  private:
      void SetColor(int font,int background);


};
#endif // BOARD_H_
