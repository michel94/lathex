#include "Common.h"

int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 600;
int SCREEN_BPP = 32;
int boardWidth = 13;
int boardHeight = 13;
int upMargin = 20, sideMargin = 20;

double size;

const int fps = 10;
int resetTime = 0;

sf::RenderWindow App;
Board *mainboard;

Player *pls[2];
int currentPl = 0;
bool played = false;
int gameState = RUNNING;

void gameCycle()
{
  if (gameState == RUNNING)
  {
    if (played)
    {
      currentPl = 1 - currentPl;
      played = false;
    }
    if (!pls[currentPl]->isHuman())
    {
      Move m = Bot::AIplay(mainboard, currentPl);
      mainboard->play(m.c, m.l, currentPl);
      played = true;
    }
    if (mainboard->checkWinner() != -1)
    {
      printf("Game Over!\nWinner: %d\n", mainboard->checkWinner());
      gameState = OVER;
    }
  }
}

int main(int argc, char** argv)
{
  sf::ContextSettings cs;
  cs.antialiasingLevel = 16;
  App.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), "LatHex Bot", !sf::Style::Resize | sf::Style::Close, sf::ContextSettings(24,8,8));
  mainboard = new Board();
  pls[0] = new Player(HUMAN);
  pls[1] = new Player(AI);
  while(App.isOpen())
  {
    gameCycle();
    sf::Event event;
    while(App.pollEvent(event)){
      switch(event.type){
      case sf::Event::Closed:
	App.close();
	break;
      case sf::Event::MouseButtonReleased:
	if (gameState == RUNNING)
	{
	  if (pls[currentPl]->isHuman())
	    if (mainboard->click(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y, currentPl))
	      played = true;
	  //printf("MouseButtonReleased at: %d, %d\n", sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
	  break;
	}
      }
    }
    
    //printf("%d", App.getSettings().antialiasingLevel);
    App.clear(sf::Color(19,20,17));
    mainboard -> draw();
    sf::Font font;
    if (!font.loadFromFile("img/ledFont.otf"))
      return EXIT_FAILURE;
    sf::Text Utext("System and Graphics by Michel (DEI/UC) > Bot by Pedro Paredes (DCC/FCUP)", font, 14);
    Utext.setPosition(10, SCREEN_HEIGHT - 20);
    sf::Text Dtext(" <Lat Hex> A Hex Bot", font, 16);
    Dtext.setPosition(40, 5);
    App.draw(Utext);
    App.draw(Dtext);
    App.display();
  }
  
  return 0;
}

//(017,046,113)
