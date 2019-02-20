#include "Board.h"
Board::Board(string WinName, unsigned DimX, unsigned DimY)
{
    WindowName = WinName;
    sf::ContextSettings Settings;
    Settings.antialiasingLevel = AntiAliasing;
    Window.create(sf::VideoMode(DimX, DimY), WindowName, sf::Style::Titlebar, Settings); //set to titlebar to remove resizing capabilities
    if (FrameRateLimit >= 0)
        Window.setFramerateLimit(FrameRateLimit); // Window.setVerticalSyncEnabled(true);
    Window.setVerticalSyncEnabled(Vsync);
    Window.setKeyRepeatEnabled(RepeatedInput);
    try //to load icon and fonts
    {
        if (!Icon.loadFromMemory(Snake_Icon_png, Snake_Icon_png_len))
            throw 1;
        if (!Font.loadFromMemory(Snake_Font, Snake_Font_len))
            throw 2;
    }
    catch(int error)
    {
        if(error == 1)
            cout << "Error loading Icon" << endl;
        else if(error == 2)
            cout << "Error loading font" << endl;
    }
    Window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
}
void Board::Fullscreen()
{
    //declare static members to remember previous states of the window
    static bool IsFullscreen = false;
    static const unsigned WindowDimentionX = Window.getSize().x;
    static const unsigned WindowDimentionY = Window.getSize().y;
    if(!IsFullscreen)
    {
        Window.close();
        Window.create(sf::VideoMode::getDesktopMode(), WindowName, sf::Style::Fullscreen); //Window is not a pointer, no memory leaks i hope
        IsFullscreen = true;
    }
    else
    {
        Window.close();
        Window.create(sf::VideoMode(WindowDimentionX, WindowDimentionY), WindowName, sf::Style::Titlebar, Window.getSettings());
        IsFullscreen = false;
    }
}
Board::~Board()
{
}