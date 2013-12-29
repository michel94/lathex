#ifndef PLAYER
#define PLAYER

#define AI 314
#define HUMAN 271

class Player
{
  private:
    int type;
  public:
    Player();
    Player(int _type);
    bool isHuman();
};

#endif
