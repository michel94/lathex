#include "Common.h"

sf::Texture imgEmpty;
sf::Texture imgplayer1;
sf::Texture imgplayer2;
sf::Sprite sp;
double x=0, y=0, dx=1, dy=1;
int type;

Object::Object()
{

}


Object::Object(int settype, float setx, float sety)
{
  imgEmpty.loadFromFile("img/hex.png");
  imgplayer1.loadFromFile("img/player1.png");
  imgplayer2.loadFromFile("img/player2.png");
  imgEmpty.setSmooth(true);
//  if(settype == -1);
  sp.setTexture(imgEmpty);
  sp.scale(size/sp.getGlobalBounds().width,size/sp.getGlobalBounds().height);
  type = settype;
  x = setx; y = sety;
  sp.setPosition(x, y);
}

void Object::draw()
{
  App.draw(sp);
}

void Object::changeHex(int player)
{
  if (player == 0)
  {
    sp.setTexture(imgplayer1);
    type = 0;
  }
  else if (player == 1)
  {
    sp.setTexture(imgplayer2);
    type = 1;
  }
  else
  {
    sp.setTexture(imgEmpty);
    type = -1;
  }
}
