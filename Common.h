#ifndef COMMON
#define COMMON

struct Move
{
  int c, l;
} typedef Move;

#define RUNNING 111
#define OVER 112

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "main.h"
#include <stdio.h>
#include <math.h>

#endif
