#include<iostream>
#include<iomanip>
#include<windows.h>
#ifndef BOARD_H_
#define BOARD_H_
class Board
{
  public:
      Board(){};
      ~Board(){};
      Board(int size){};

      int size = 4;
      int** board = NULL;
      bool Create();
      void Print();
      void Delete();
  private:
      void SetColor(int font,int background);

};
#endif // BOARD_H_
