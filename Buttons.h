#ifndef BUTTONS_H
#define BUTTONS_H
#include "Board.h"
class Buttons
{
private:
  /**
   * set these to null so as to check if text exists or not, also helps with memory management
   */
  sf::Shape *Button = nullptr;
  Board *GameBoard = nullptr;
  sf::Text *ButtonText = nullptr;

public:
  /**
   * \Initiate button object
   * \Takes Board object as input, does not take board object anymore
   */
  Buttons(Board *board);
  /**
   * \Creates rectangular button with custom pos and size
   * \Optional text input, if no button object exists, use the other functions in the class to create a text object here instead
   * \Automatically centers text as well if given
   */
  void CreateRect(sf::Vector2f origin, sf::Vector2f size, sf::Text *ButtonText = nullptr);
  /**
   * \Creates circular button with custom pos and radius
   * \Optional circle point count
   * \Optional text input, if no button object exists, use the other functions in the class to create a text object here instead
   * \Automatically centers text as well if given
   */
  void CreateCircle(sf::Vector2f origin, float radius, size_t PointCount = 30, sf::Text *ButtonText = nullptr);
  //TODO:
  //void CreateConvex()
  /**
   * \Set the text for the button, 
   * \Also centers text as well
   */
  void setText(sf::Color fill, string text, unsigned Textsize = 18, sf::Color outline = sf::Color::Black, float thinkness = 0); // alternative way to set text, colors and centers it
  /**
   * \Set the button colors and outlines
   */
  void setColors(sf::Color fill, sf::Color outline = sf::Color::Black, float thickness = 1);
  void CenterText();
  /**
   * \Draw the button on the board object that was given in the constructor
   * \No exceptions thrown, make sure passed object still exists
   */
  void draw();
  bool ShapeContainsMouse();
  /**
   * \Check if button was hovered over
   */
  bool IsHovered();
  /**
   * \Check if button was clicked
   */
  bool IsClicked();
  /**
   * \Check if button was released
   */
  bool IsReleased();
  ~Buttons();
};
#endif