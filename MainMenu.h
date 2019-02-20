#ifndef MAINMENU_H
#define MAINMENU_H
#include "Board.h"
#include "Buttons.h"
#include "Data/Main_Menu_Background.h"
class MainMenu
{
private:
    Board *GameBoard = nullptr; //pointer to Board object that will be used in class
    sf::Texture BGTexture;
    sf::Sprite Background; //These two are used in multiple locations, thus why they are globally defined for the class
    //NOTE: since these three are declared together, one of them set to null so they don't get deleted on the first go(seg fault)
    Buttons *PlayButton, *QuitButton, *FullScreen;  
public:
    /**
     * \Create a mainMenu object in the given Board object, Uses provided main menu image file in Data folder as background
     * \Change button locations from the cpp file
     * //TODO: recieve button locations and sizes somehow..
     */
    MainMenu(Board *);
    /**
     * \Creates mainMenu interface, also the buttons change color based on whether they are hovered over
     * \Returs int value based on what button was pressed, 1 for play and 0 for quit
     */
    int Loop();
    void RebuildMenu();
    void CreateButtons();
    ~MainMenu();
};
#endif 