#include "Snake.h"
#include <time.h>
#include <cstdlib>
Snake::Snake(Board *mainBoard)
{
    gameBoard = mainBoard;
    QuitButton = new Buttons(gameBoard);
    GoBack = new Buttons(gameBoard);
    Fullscreen = new Buttons(gameBoard);
    PressEnterToPlay = new sf::Text;
    //this part is identical to part of rebuildMenu()
    CreateButtons();

    //declare one time properties, info that is changed should be put in RebuildMenu()
    scoreText.setFont(gameBoard->Font);
    scoreText.setFillColor(TextColor);

    PressEnterToPlay->setFont(gameBoard->Font);
    PressEnterToPlay->setFillColor(TextColor);
    PressEnterToPlay->setString("Press space to play!");
    PressEnterToPlay->setPosition(sf::Vector2f(gameBoard->Window.getSize().x / 2, menubarHeight + gameBoard->Window.getSize().y / 2));
    //move to center:
    PressEnterToPlay->move(-sf::Vector2f(PressEnterToPlay->getGlobalBounds().width / 2, PressEnterToPlay->getGlobalBounds().height / 2 + PressEnterToPlay->getCharacterSize() / 4)); //move so text is in the middle of button

    upperBar.setSize(sf::Vector2f(gameBoard->Window.getSize().x, menubarHeight));
    upperBar.setFillColor(BarFillColor);

    playBar.setFillColor(GameBackground);
    playBar.setPosition(sf::Vector2f(0, menubarHeight));
    playBar.setSize(sf::Vector2f(gameBoard->Window.getSize().x, gameBoard->Window.getSize().y - menubarHeight));

    //initial declaration of body and food
    snakeBody = new deque<SnakeInfo>;
    for (int y = YblockNum / 2 - 1; y <= YblockNum / 2 + 1; y++)
    {
        SnakeInfo temp;
        unsigned x = XblockNum / 2;
        temp.Xnum = x;
        temp.Ynum = y;
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_back(temp); // first element will be head, rest will follow behind
        snakeBody->back().Rect.setFillColor(HeadColor);
        HeadColor = darkenColor(HeadColor, 0.97);
    }
    food = new FoodInfo;
    CheckAndUpdateFood(nullptr);
}
void Snake::RebuildMenu(char status)
{
    if (status == 'N')
    {
        PressEnterToPlay->setPosition(sf::Vector2f(gameBoard->Window.getSize().x / 2, menubarHeight + gameBoard->Window.getSize().y / 2));
        //move to center:
        PressEnterToPlay->move(-sf::Vector2f(PressEnterToPlay->getGlobalBounds().width / 2, PressEnterToPlay->getGlobalBounds().height / 2 + PressEnterToPlay->getCharacterSize() / 4)); //move so text is in the middle of button
    }
    else if (status == 'P')
    {
        PressEnterToPlay->setPosition(sf::Vector2f(gameBoard->Window.getSize().x / 2, menubarHeight + gameBoard->Window.getSize().y / 2));
        //move to center:
        PressEnterToPlay->move(-sf::Vector2f(PressEnterToPlay->getGlobalBounds().width / 2, PressEnterToPlay->getGlobalBounds().height / 2 + PressEnterToPlay->getCharacterSize() / 4)); //move so text is in the middle of button
        scoreText.setPosition(sf::Vector2f(gameBoard->Window.getSize().x / 2, 0));
    }
    else if (status == 'Y')
        scoreText.setPosition(sf::Vector2f(gameBoard->Window.getSize().x / 2, 0));
    //Set new snake block pos' and size's
    for (deque<SnakeInfo>::iterator it = snakeBody->begin(); it != snakeBody->end(); it++)
    {
        it->Rect.setPosition(GetSnakeBlockAtPos(it->Xnum, it->Ynum).getPosition());
        it->Rect.setSize(GetSnakeBlockAtPos(it->Xnum, it->Ynum).getSize());
    }
    //Set new food block pos
    food->Circ.setPosition(GetFoodBlockAtPos(food->Xnum, food->Ynum).getPosition());
    //set bar pos' and size's
    upperBar.setSize(sf::Vector2f(gameBoard->Window.getSize().x, menubarHeight));
    playBar.setPosition(sf::Vector2f(0, menubarHeight));
    playBar.setSize(sf::Vector2f(gameBoard->Window.getSize().x, gameBoard->Window.getSize().y - menubarHeight));
    //create buttons and bars
    CreateButtons();
}
void Snake::CreateButtons()
{
    //create buttons
    Fullscreen->CreateRect(sf::Vector2f(gameBoard->Window.getSize().x - 100, 0), sf::Vector2f(100, menubarHeight));
    GoBack->CreateRect(sf::Vector2f(gameBoard->Window.getSize().x - 210, 0), sf::Vector2f(100, menubarHeight));
    QuitButton->CreateRect(sf::Vector2f(0, 0), sf::Vector2f(100, menubarHeight));
    //set text, also centers it
    GoBack->setText(TextColor, "GO BACK", 10);
    QuitButton->setText(TextColor, "QUIT", 15);
    Fullscreen->setText(TextColor, "FULLSCREEN", 10);
    
}
int Snake::Loop()
{
    char ThisHeadDir = 'U'; 
    char NextHeadDir = ' '; //nothing in it for now// these make for 2 saved movements maximum
    bool secondaryDir = false; 
    char status = 'N';
    bool needfood = false; //starts with a food already
    sf::Clock clock;
    while (gameBoard->Window.isOpen())
    {
        while (gameBoard->Window.pollEvent(gameBoard->Event))
        {
            if (gameBoard->Event.type == sf::Event::Closed)
                gameBoard->Window.close();
            if (QuitButton->IsClicked())
                return 0; // quit
            else if (GoBack->IsClicked())
                return 1; // go back
            else if (Fullscreen->IsClicked())
            {
                Fullscreen->setColors(sf::Color(191, 192, 193));
                gameBoard->Window.clear(); // clear page so old objects are deleted
                gameBoard->Fullscreen();
                if(status == 'Y')
                    status = 'P';
                RebuildMenu(status);
                clock.restart();
            }
            else if (QuitButton->IsHovered())
                QuitButton->setColors(sf::Color(191, 192, 193));
            else if (GoBack->IsHovered())
                GoBack->setColors(sf::Color(191, 192, 193));
            else if (Fullscreen->IsHovered())
                Fullscreen->setColors(sf::Color(191, 192, 193));
            else
            {
                Fullscreen->setColors(sf::Color(209, 210, 211));
                QuitButton->setColors(sf::Color(209, 210, 211));
                GoBack->setColors(sf::Color(209, 210, 211));
            }
            if (gameBoard->Event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //pause and resume
                {
                    if(status == 'Y')
                        status = 'P';
                    else if( status == 'N')
                        status = 'Y';
                    else if(status == 'P')
                        status = 'Y';
                    RebuildMenu(status);
                    clock.restart();
                }
                else if (status == 'Y')
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        if (!secondaryDir && ThisHeadDir != 'D')
                        {
                            secondaryDir = true;
                            ThisHeadDir = 'U';
                        }
                        else if (ThisHeadDir != 'D')
                            NextHeadDir = 'U';
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    {
                        if (!secondaryDir && ThisHeadDir != 'U')
                        {
                            secondaryDir = true;
                            ThisHeadDir = 'D';
                        }
                        else if (ThisHeadDir != 'U')
                            NextHeadDir = 'D';
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        if (!secondaryDir && ThisHeadDir != 'R')
                        {
                            secondaryDir = true;
                            ThisHeadDir = 'L';
                        }
                        else if (ThisHeadDir != 'R')
                            NextHeadDir = 'L';
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    {
                        if (!secondaryDir && ThisHeadDir != 'L')
                        {
                            secondaryDir = true;
                            ThisHeadDir = 'R';
                        }
                        else if (ThisHeadDir != 'L')
                            NextHeadDir = 'R';
                    }
                }
            }
        }
        gameBoard->Window.clear();
        //UpperBar
        gameBoard->Window.draw(upperBar);
        QuitButton->draw();
        GoBack->draw();
        Fullscreen->draw();
        //playBar
        gameBoard->Window.draw(playBar);
        if (status == 'N') // if already not started,
            gameBoard->Window.draw(*PressEnterToPlay);
        else if (status == 'Y') //playing
        {
            scoreText.setString(to_string(Score)); // score given in another func
            gameBoard->Window.draw(scoreText);
            if (clock.getElapsedTime().asMilliseconds() > waitTimeMS) //update time
            {
                if (!CheckAndUpdateSnake(ThisHeadDir, &needfood))
                    return 2; // lost
                if (needfood && !CheckAndUpdateFood(&needfood))
                    return 3; // won
                if (NextHeadDir != ' ')
                {
                    ThisHeadDir = NextHeadDir;
                    NextHeadDir = ' ';
                }
                secondaryDir = false;
                clock.restart();
            }
            for (deque<SnakeInfo>::iterator it = snakeBody->begin(); it != snakeBody->end(); it++)
                gameBoard->Window.draw(it->Rect);
            gameBoard->Window.draw(food->Circ);
        }
        else if (status == 'P') // pause
        {
            scoreText.setString(to_string(Score)); // score given in another func
            gameBoard->Window.draw(scoreText);
            gameBoard->Window.draw(food->Circ);
            for (deque<SnakeInfo>::iterator it = snakeBody->begin(); it != snakeBody->end(); it++)
                gameBoard->Window.draw(it->Rect);
            gameBoard->Window.draw(*PressEnterToPlay);            
        }
        gameBoard->Window.display();
    }
    return 0; //quit window, exit
}
bool Snake::CheckAndUpdateSnake(char headDir, bool *needfood)
{
    //direction check
    if (headDir == 'U')
    {
        if (snakeBody->front().Ynum == 1)
            return false;
        SnakeInfo temp;
        temp.Xnum = snakeBody->front().Xnum;
        temp.Ynum = (snakeBody->front().Ynum - 1);
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_front(temp); // new head pos
        for(unsigned i = 1 ; i < snakeBody->size() ; i++)
            snakeBody->at(i-1).Rect.setFillColor(snakeBody->at(i).Rect.getFillColor());
        snakeBody->pop_back();
    }
    else if (headDir == 'D')
    {
        if (snakeBody->front().Ynum == YblockNum)
            return false;
        SnakeInfo temp;
        temp.Xnum = snakeBody->front().Xnum;
        temp.Ynum = (snakeBody->front().Ynum + 1);
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_front(temp); // new head pos
        for(unsigned i = 1 ; i < snakeBody->size() ; i++)
            snakeBody->at(i-1).Rect.setFillColor(snakeBody->at(i).Rect.getFillColor());
        snakeBody->pop_back();
    }
    else if (headDir == 'L')
    {
        if (snakeBody->front().Xnum == 1)
            return false;
        SnakeInfo temp;
        temp.Xnum = (snakeBody->front().Xnum) - 1;
        temp.Ynum = snakeBody->front().Ynum;
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_front(temp); // new head pos
        for(unsigned i = 1 ; i < snakeBody->size() ; i++)
            snakeBody->at(i-1).Rect.setFillColor(snakeBody->at(i).Rect.getFillColor());
        snakeBody->pop_back();
    }
    else if (headDir == 'R')
    {
        if (snakeBody->front().Xnum == XblockNum)
            return false;
        SnakeInfo temp;
        temp.Xnum = (snakeBody->front().Xnum) + 1;
        temp.Ynum = snakeBody->front().Ynum;
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_front(temp); // new head pos
        for(unsigned i = 1 ; i < snakeBody->size() ; i++)
            snakeBody->at(i-1).Rect.setFillColor(snakeBody->at(i).Rect.getFillColor());
        snakeBody->pop_back();
    }
    //food consumed check
    if (snakeBody->front().Xnum == food->Xnum && snakeBody->front().Ynum == food->Ynum) // head has eaten food
    {
        *needfood = true;
        SnakeInfo temp;
        temp.Xnum = snakeBody->back().Xnum;
        temp.Ynum = snakeBody->back().Ynum;
        temp.Rect = GetSnakeBlockAtPos(temp.Xnum, temp.Ynum);
        snakeBody->push_back(temp); // add new block in the place of the tail
        snakeBody->back().Rect.setFillColor(HeadColor);
        HeadColor = darkenColor(HeadColor, 0.97);
        Score++;
    }
    //self consumed check
    for(unsigned i = 1 ; i < snakeBody->size() ; i++)
        if (snakeBody->at(i).Xnum == snakeBody->at(0).Xnum && snakeBody->at(i).Ynum == snakeBody->at(0).Ynum)
            return false;
    return true;
}
bool Snake::CheckAndUpdateFood(bool *needfood)
{
    list<sf::Vector2u> possibleFoodLoc; //(x,y) pos of all possible locations
    for (int i = 1; i <= YblockNum; i++)
        for (int j = 1; j <= XblockNum; j++)
            possibleFoodLoc.push_back(sf::Vector2u(j, i));
    for (deque<SnakeInfo>::iterator it = snakeBody->begin(); it != snakeBody->end(); it++)
        possibleFoodLoc.remove(sf::Vector2u(it->Xnum, it->Ynum)); //remove those that are not allowed
    if (possibleFoodLoc.empty())
        return false; // game is won when no other food can be placed! put this function before updateSnake func!
    srand(time(0));
    unsigned randelement = rand() % possibleFoodLoc.size();
    unsigned iterator = 0;
    for (list<sf::Vector2u>::iterator it = possibleFoodLoc.begin(); it != possibleFoodLoc.end(); it++)
    {
        if (iterator == randelement)
        {
            food->Xnum = it->x;
            food->Ynum = it->y;
            food->Circ = GetFoodBlockAtPos(food->Xnum, food->Ynum);
            break;
        }
        iterator++;
    }
    if (needfood != nullptr) // for constructor check
        *needfood = false;
    return true;
}
sf::RectangleShape Snake::GetSnakeBlockAtPos(unsigned Xnum, unsigned Ynum)
{
    sf::RectangleShape returnrect;
    float Xstep = (float)gameBoard->Window.getSize().x / XblockNum;
    float Ystep = (float)(gameBoard->Window.getSize().y - menubarHeight) / YblockNum; //must not be declared static, as it might change after resize of screen(alternatively do a global check)
    returnrect.setPosition(sf::Vector2f((Xnum - 1) * Xstep, menubarHeight + (Ynum - 1) * Ystep));
    returnrect.setSize(sf::Vector2f(Xstep, Ystep));
    returnrect.setOutlineColor(OutlineColor);
    returnrect.setOutlineThickness(1);
    return returnrect;
}
sf::CircleShape Snake::GetFoodBlockAtPos(unsigned Xnum, unsigned Ynum)
{
    sf::CircleShape returncir;
    float Xstep = (float)gameBoard->Window.getSize().x / XblockNum;
    float Ystep = (float)(gameBoard->Window.getSize().y - menubarHeight) / YblockNum; //must not be declared static, as it might change after resize of screen(alternatively do a global check)
    float radius = (float)min(Xstep, Ystep) / 4;
    returncir.setFillColor(FoodColor);
    returncir.setPosition(sf::Vector2f((Xnum - 1) * Xstep, menubarHeight + (Ynum - 1) * Ystep));
    returncir.move(sf::Vector2f(Xstep / 2 - radius, Ystep / 2 - radius));
    returncir.setRadius(radius);
    returncir.setOutlineColor(OutlineColor);
    returncir.setOutlineThickness(1);

    return returncir;
}
sf::Color Snake::darkenColor(sf::Color color, float tint_factor)
{
    int newR = ((int)color.r) * tint_factor;
    int newG = ((int)color.g) * tint_factor;
    int newB = ((int)color.b) * tint_factor;
    return sf::Color(newR, newG, newB);
}
Snake::~Snake()
{
    if(PressEnterToPlay != nullptr)
        delete PressEnterToPlay;
    delete QuitButton;
    delete GoBack;
    delete Fullscreen;
    delete snakeBody;
    delete food;
    gameBoard = nullptr;
}