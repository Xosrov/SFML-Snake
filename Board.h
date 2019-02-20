#ifndef BOARD_H
#define BOARD_H
#include <string>            // Overall use in names
#include "SFML/Graphics.hpp" // Using sfml libraries
#include "Data/Icon.h"       // Icon file in the same dir
#include "Data/Font.h"       // Font file // /// //// ///
#include <iostream>          // Used for exception handling and debugging
#include <list>              // Usefull for creating list of objects
#include <deque>             // Alternative for list in special cases where individual access needed
#define FrameRateLimit 0     // set to -1 if Vsync is on
#define Vsync false
#define AntiAliasing 8
#define RepeatedInput true
using namespace std; // Easy access, remove if conflicts occur
class Board
{
public:
  sf::View windowView; // used for resizing
  sf::RenderWindow Window;
  sf::Event Event;
  // window data
  string WindowName;
  sf::Image Icon;
  sf::Font Font;
  /**
   * \Construct Board(Game window) with given dimentions and name
   * \Makes use of some custom settings as well which can be changed or added to from the .h file
   * \Also loads Icon and Font files from "Data" folder in current dir, one font supported only for now, note the file names and contents need to match a certain format too
   */
  Board(string Name, unsigned DimentionX, unsigned DimentionY);
  /**
   * \Switch the screen to fullscreen by getting maximum window size, set to titlebar mode as well for best effect
   */
  void Fullscreen(); //switch fullscreen and windowed
  ~Board();
};

#endif