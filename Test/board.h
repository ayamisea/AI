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
      Board(int size){};

      int size = 4;
      int** board = NULL;
      bool Create();
      void Display();
      void Delete();
      bool PositionExist(int r,int c);
      void setRandColor(int rc){randColor=rc;}
      int getRandColor() const {return randColor;}
      bool performMove(const Position &p,int pyNo);
      int getNumRemainBricks(int pyNo)const;
      std::vector<Position> getRemainBricks(int pyNo)const;

  private:
      void SetColor(int font,int background);
      int randColor=1;
      bool Stay(int r,int c);

};
#endif // BOARD_H_
