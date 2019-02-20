#include "MainMenu.h"
MainMenu::MainMenu(Board *mainBoard)
{
    GameBoard = mainBoard;
    try
    {
        if (!BGTexture.loadFromMemory(Main_Menu_Background, Main_Menu_Background_len))
            throw 1;
    }
    catch (int error)
    {
        if (error == 1)
            cout << "Could not load background" << endl;
    }
    Background.setTexture(BGTexture);
    PlayButton = new Buttons(GameBoard);
    QuitButton = new Buttons(GameBoard);
    FullScreen = new Buttons(GameBoard);
    RebuildMenu();
}
void MainMenu::RebuildMenu()
{
    Background.setTextureRect(sf::IntRect((BGTexture.getSize().x - GameBoard->Window.getSize().x) / 2,
                                          (BGTexture.getSize().y - GameBoard->Window.getSize().y) / 2,
                                          GameBoard->Window.getSize().x,
                                          GameBoard->Window.getSize().y)); // Background set to middle part of the Image, works even if window size changes
    //buttons
    CreateButtons();
}
void MainMenu::CreateButtons()
{
    //create buttons with arbitrary text, size and positions in window, edit as desired
    PlayButton->CreateRect(sf::Vector2f((float)GameBoard->Window.getSize().x / 2 - 100, (float)GameBoard->Window.getSize().y / 2 - 300), sf::Vector2f(200, 100));
    PlayButton->setText(sf::Color::Black, "PLAY", 30);

    QuitButton->CreateRect(sf::Vector2f((float)GameBoard->Window.getSize().x / 2 - 100, (float)GameBoard->Window.getSize().y / 2 - 100), sf::Vector2f(200, 100));
    QuitButton->setText(sf::Color::Black, "QUIT", 30);

    FullScreen->CreateRect(sf::Vector2f(0, 0), sf::Vector2f(100, 50));
    FullScreen->setText(sf::Color::Black, "FULLSCREEN", 10);
}
int MainMenu::Loop()
{
    while (GameBoard->Window.isOpen())
    {
        while (GameBoard->Window.pollEvent(GameBoard->Event))
        {
            if (GameBoard->Event.type == sf::Event::Closed)
                GameBoard->Window.close();

            if (PlayButton->IsClicked())
                return 1;
            else if (QuitButton->IsClicked())
                return 0;
            else if (FullScreen->IsClicked())
            {
                FullScreen->setColors(sf::Color(145, 145, 145)); //these colors are checking whether button is pressed, clicked or hovered and changing their color
                GameBoard->Fullscreen();
                RebuildMenu();
            }
            else if (PlayButton->IsHovered())
                PlayButton->setColors(sf::Color(191, 192, 193));
            else if (QuitButton->IsHovered())
                QuitButton->setColors(sf::Color(191, 192, 193));
            else if (FullScreen->IsHovered())
                FullScreen->setColors(sf::Color(191, 192, 193));
            else
            {
                PlayButton->setColors(sf::Color(209, 210, 211));
                QuitButton->setColors(sf::Color(209, 210, 211));
                FullScreen->setColors(sf::Color(209, 210, 211));
            }
        }
        GameBoard->Window.clear();
        GameBoard->Window.draw(Background);
        PlayButton->draw();
        QuitButton->draw();
        FullScreen->draw();
        GameBoard->Window.display();
    }
    return 0; // quit if closed window
}
MainMenu::~MainMenu()
{
    delete PlayButton;
    delete QuitButton;
    delete FullScreen;
    GameBoard = nullptr; //Gameboard may be used by other functions outside class, do not delete it
}
