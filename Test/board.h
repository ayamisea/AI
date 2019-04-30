#include<iostream>
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
      void print();
      void Delete();

};
#endif // BOARD_H_
