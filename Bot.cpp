#include "Common.h"

Move Bot::AIplay(Board *b, int player)
{
  Move bestMove;
  bestMove.c = 0;
  bestMove.l = 0;
  while (b->checkHex(bestMove.c, bestMove.l) != -1)
  {
    bestMove.c++;
    if (bestMove.c == boardWidth)
    {
      bestMove.c = 0;
      bestMove.l++;
    }
  }
  return bestMove;
}
