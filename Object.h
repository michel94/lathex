#ifndef OBJECT
#define OBJECT

#include "Common.h"

class Object
{
  private:
    sf::Sprite sp;
	
  public:
    Object();
    Object(int type, float setx, float sety);
    int type;
    double x, y, dx, dy;
    void draw();
    void changeHex(int player);	
};

#endif
