#include "Common.h"

Object *(hexagons[15][15]);
sf::Texture imgborder0, imgborder1;
sf::Sprite borderVer1[15];
sf::Sprite borderVer0[15];
sf::Sprite borderHor0[15];
sf::Sprite borderHor1[15];

struct Point
{
  double x, y;
} typedef Point;

double min(double a, double b)
{
  return (a < b) ? a : b;
}

Board::Point Board::findClickedHex(int setx, int sety, int player)
{
  double x = -1, y = -1;
  for(int l=0; l < boardHeight; l++)
  {
    for(int c=0; c < boardWidth; c++)
    {		
      x = (hexagons[c][l]) -> x;
      y = (hexagons[c][l]) -> y;
      x += size/2;
      y += size/2;
      if (pow(x-setx, 2) + pow(y-sety, 2) <= pow((double)size/2,2))
      {
	if(checkHex(c, l) == -1)
	{
	  Point p;
	  p.x = c;
	  p.y = l;
	  return p;
	}
      }
    }
  }
  Point p;
  p.x = -1;
  p.y = -1;
  return p;
}

void Board::setupBorder()
{
  imgborder0.loadFromFile("img/border0.png");
  imgborder0.setSmooth(true);
  imgborder1.loadFromFile("img/border1.png");
  imgborder1.setSmooth(true);
  for(int i = 0; i < boardHeight; i++)
  {
    borderVer1[i].setTexture(imgborder0);
    borderVer1[i].scale(size/400.0,size/400.0);
    borderVer1[i].setRotation(-30);
    borderVer1[i].setPosition(5 + size/2 + hexagons[boardHeight-1][i] -> x, -5 + hexagons[boardHeight-1][i] -> y);
  }
  for(int i = 0; i < boardHeight; i++)
  {
    borderVer0[i].setTexture(imgborder0);
    borderVer0[i].scale(size/400.0,size/400.0);
    borderVer0[i].setRotation(150);
    borderVer0[i].setPosition(-5 + size/2 + hexagons[0][i] -> x, 5 + size + hexagons[0][i] -> y);
  }
  for(int i = 0; i < boardWidth; i++)
  {
    borderHor1[i].setTexture(imgborder1);
    borderHor1[i].scale(size/400.0,size/400.0);
    borderHor1[i].setRotation(180);
    borderHor1[i].setPosition(size + hexagons[i][boardHeight-1] -> x, 6 + size + size/4 + hexagons[i][boardHeight-1] -> y);
  }
  for(int i = 0; i < boardWidth; i++)
  {
    borderHor0[i].setTexture(imgborder1);
    borderHor0[i].scale(size/400.0,size/400.0);
    borderHor0[i].setRotation(0);
    borderHor0[i].setPosition(hexagons[i][0] -> x, -6 + -size/4 + hexagons[i][0] -> y);
  }
}

Board::Board()
{
  setupBoard();
  setupBorder();
}

void Board::play(int c, int l, int _player)
{
  hexagons[c][l]->changeHex(_player);
}
void Board::unplay(int c, int l)
{
  hexagons[c][l]->changeHex(-1);
}

int Board::checkHex(int c, int l)
{
  return hexagons[c][l]->type;
}

void Board::draw()
{
  for(int l = 0; l < boardHeight; l++)
  {
    for(int c = 0; c < boardWidth; c++)
    {
      hexagons[c][l] -> draw();
    }
  }
  for(int i = 0; i < boardHeight; i++)
  {
    App.draw(borderVer0[i]);
  }
  for(int i = 0; i < boardHeight; i++)
  {
    App.draw(borderVer1[i]);
  }
  for(int i = 0; i < boardWidth; i++)
  {
    App.draw(borderHor0[i]);
  }
  for(int i = 0; i < boardWidth; i++)
  {
    App.draw(borderHor1[i]);
  }
}

void Board::setupBoard()
{
  int a = (SCREEN_WIDTH - 2*sideMargin)/( boardWidth + ((double)boardHeight-1)/2);
  int b = (SCREEN_HEIGHT - 2*upMargin)/(1+(sqrt(3)/2)*(boardHeight-1));
  size = min(a , b);
  int r = size*((boardHeight-1)/2+boardWidth);
  int s = size*(1+(sqrt(3)/2)*(boardHeight-1));
  for(int l=0; l < boardHeight; l++){
    for(int c=0; c < boardWidth; c++){
      hexagons[c][l] = new Object(-1, sideMargin + ((SCREEN_WIDTH - 2*sideMargin) - r )/2  + c*(size) + l*((size)/2), upMargin + ((SCREEN_HEIGHT - 2*upMargin) - s )/2 + l*((sqrt(3)*size)/2));
    }
  }

}

bool Board::click(int setx, int sety, int player)
{	
  Point p;
  p = findClickedHex(setx, sety, player);
	
  if(p.x == -1 && p.y == -1)
  {
    return false;
  }
  else
  {
    play(p.x, p.y, player);
    return true;
  }
}

int Board::findpath(bool vis[15][15], int cx, int cy, int type)
{
  int res = 0;
	
  vis[cy][cx] = true;
	
  if(type==0 && cy==boardWidth-1){
    return 1;
  }
  if(type==1 && cx==boardHeight-1){
    return 1;
  }

  if(testHex(vis, cx, cy - 1, type)){
    res += findpath(vis, cx, cy-1, type);
  }
  if(testHex(vis, cx +1, cy - 1, type)){
    res += findpath(vis, cx+1, cy-1, type);
  }
  if(testHex(vis, cx + 1, cy, type)){
    res += findpath(vis, cx+1, cy, type);
  }
  if(testHex(vis, cx, cy+1, type)){
    res += findpath(vis, cx, cy+1, type);
  }
  if(testHex(vis, cx - 1, cy +1, type)){
    res += findpath(vis, cx-1, cy+1, type);
  }
  if(testHex(vis, cx - 1, cy, type)){
    res += findpath(vis, cx-1, cy, type);
  }
  return res;

}

bool Board::testHex(bool vis[15][15], int x, int y, int type)
{
  if(x>=0 && x<boardWidth && y>=0 && y<boardHeight){
    if(vis[y][x] == false && hexagons[y][x] -> type == type){
      return true;
    }
  }
  return false;
}

int Board::checkWinner()
{
  int hor=0, ver=0;
  bool vis[15][15];
  for(int i=0; i<15; i++){
    for(int o=0; o<15; o++){
      vis[i][o] = 0;
    }
  }
  for(int x=0; x<boardHeight; x++){
    if(hexagons[0][x] -> type == 0){
      hor = findpath(vis, x, 0, 0);
    }
  }
  for(int y=0; y<boardWidth; y++){
    if(hexagons[y][0] -> type == 1){
      ver = findpath(vis, 0, y, 1);
    }
  }
  if(hor > 0)
    return 0;
  if(ver > 0)
    return 1;
	
  return -1;
}
