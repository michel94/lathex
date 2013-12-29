#ifndef BOARD
#define BOARD

#include "Common.h"

class Board
{
  private:
    Object *(hexagons[15][15]);
    struct Point
    {
      double x, y;
    }typedef Point;
    void setupBoard();
    void setupBorder();
    int findpath(bool vis[15][15], int cx, int cy, int type);
    bool testHex(bool vis[15][15], int x, int y, int type);
    Point findClickedHex(int setx, int sety, int player);

  public:
    Board();
    void draw();
    bool click(int setx, int sety, int player);
    void play(int c, int l, int _player);
    void unplay(int c, int l);
    int checkHex(int c, int l);
    int checkWinner();
};

#endif
