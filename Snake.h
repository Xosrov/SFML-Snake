#ifndef SNAKE_H
#define SNAKE_H
#include "Buttons.h"
#include "Board.h"
#define waitTimeMS 150
#define menubarHeight 60
#define TextColor sf::Color::Black
#define OutlineColor sf::Color::Black
#define BarFillColor sf::Color::White
#define FoodColor sf::Color::Red
#define XblockNum 16
#define YblockNum 16 //can't be less than 7 due to how the snake is created to begin with! (using width / 2 may end up outside the screen!)
typedef struct
{
  sf::RectangleShape Rect;
  unsigned Xnum, Ynum;
} SnakeInfo;
typedef struct
{
  sf::CircleShape Circ;
  unsigned Xnum, Ynum;
} FoodInfo;

class Snake
{
private:
  Board *gameBoard;
  //Colors that may be changed later in the game
  sf::Color GameBackground = sf::Color(0, 91, 4);
  sf::Color HeadColor = sf::Color(255, 114, 250);
  //Buttons and assets, declared as pointers since no default constructor for buttons was added, not really a problem though
  Buttons *QuitButton,*GoBack, *Fullscreen;
  //Buttons and bars
  sf::Text *PressEnterToPlay, scoreText;
  sf::RectangleShape upperBar, playBar;
  //declared from start but used only when game is started, this way no initial lag if there is any
  unsigned Score = 0;
  deque<SnakeInfo> *snakeBody;
  FoodInfo *food;

public:
  Snake(Board *);
  int Loop();                             // main loop, makes use of other functions to run the game
  void RebuildMenu(char status);         //rebuilds the menu, used in two cases: 1. when game starts to set pointer values and 2. when going fullscreen
  void CreateButtons();
  bool CheckAndUpdateSnake(char, bool *); //checks if move is allowed then performs it, so it also checks if you hit the walls or eat food
  //caution, does not fill colors, do that manually -- did this for the lightening effect
  sf::RectangleShape GetSnakeBlockAtPos(unsigned Xnum, unsigned Ynum); //returns rectangle that sits in the X'th num of the blocks the snake can move on
                                                                       //maximum input is Xblocknum and Yblocknum, anything else is not accepted.
  //does fill color, red in fact
  sf::CircleShape GetFoodBlockAtPos(unsigned Xnum, unsigned Ynum); //same as above but circle
  bool CheckAndUpdateFood(bool *);                                 // checks if food can be placed and places it, also checks if the game is over
  sf::Color darkenColor(sf::Color, float factor);                  //darken a color by a factor, factor is amount to take off rgb vals(multiply, less than 1 for darkening)
  ~Snake();
};
#endif