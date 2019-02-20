#include "Buttons.h"
Buttons::Buttons(Board *board)
{
    GameBoard = board;
}
void Buttons::CreateRect(sf::Vector2f origin, sf::Vector2f size, sf::Text *text)
{
    delete Button; //prevent memory leaks in case of reuse
    Button = new sf::RectangleShape(size);
    Button->setPosition(origin);
    delete ButtonText; //prevent memory leaks in case of reuse
    ButtonText = text;
    CenterText();
}
void Buttons::CreateCircle(sf::Vector2f origin, float radius, size_t PointCount, sf::Text *text)
{
    delete Button; //prevent memory leaks in case of reuse
    Button = new sf::CircleShape(radius, PointCount);
    Button->setPosition(origin);
    delete ButtonText; //prevent memory leaks in case of reuse
    ButtonText = text;
    CenterText();
}
void Buttons::setText(sf::Color fill, string text, unsigned size, sf::Color outline, float thickness)
{
    delete ButtonText; //prevent memory leaks in case of reuse
    ButtonText = new sf::Text;
    ButtonText->setFont(GameBoard->Font);
    ButtonText->setCharacterSize(size);
    ButtonText->setFillColor(fill);
    ButtonText->setOutlineColor(outline);
    ButtonText->setOutlineThickness(thickness);
    ButtonText->setString(text);
    CenterText();
}

void Buttons::CenterText()
{
    if(ButtonText != nullptr) //no exception thrown here, if a text doesn't exist, it will just not be drawn in draw()
    {
        ButtonText->setPosition(Button->getPosition() + sf::Vector2f(Button->getGlobalBounds().width / 2, Button->getGlobalBounds().height / 2)); // set origin to midpoint of button
        ButtonText->move(-sf::Vector2f(ButtonText->getGlobalBounds().width / 2, ButtonText->getGlobalBounds().height / 2 + ButtonText->getCharacterSize() / 4)); //move so text is in the middle of button
    }
}
void Buttons::setColors(sf::Color fill, sf::Color outline, float thickness)
{
    if(Button != nullptr) //full check happens in draw() for now just ignore
    {
        Button->setFillColor(fill);
        Button->setOutlineColor(outline);
        Button->setOutlineThickness(thickness);
    }
}
void Buttons::draw()
{
    try
    {
        if (Button != nullptr)
        {
            GameBoard->Window.draw(*Button);
            if (ButtonText != nullptr)
            {
                GameBoard->Window.draw(*ButtonText); //no text means it won't be drawn
                /* draw outline for text 
                sf::RectangleShape textBorder;
                textBorder.setPosition(ButtonText->getPosition());
                textBorder.setSize(sf::Vector2f(ButtonText->getLocalBounds().width , ButtonText->getLocalBounds().height + ButtonText->getCharacterSize() / 2));
                textBorder.setFillColor(sf::Color::Transparent);
                textBorder.setOutlineColor(sf::Color::Black);
                textBorder.setOutlineThickness(1);
                GameBoard->Window.draw(textBorder); */
            }
        }
        else
            throw 1;
    }
    catch (int error)
    {
        if(error == 1)
            cout << "No button" << endl;
    }
}
bool Buttons::ShapeContainsMouse()
{
    try
    {
        if (Button != nullptr)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(GameBoard->Window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (Button->getGlobalBounds().contains(mousePosF))
                return true;
            else
                return false;
        }
        else
            throw 1;
    }
    catch (int error)
    {
        if (error == 1)
            cout << "No button" << endl;
        return false;
    }
}
bool Buttons::IsHovered()
{
    try
    {
        if (Button != nullptr)
        {
            if (ShapeContainsMouse() && GameBoard->Event.type == sf::Event::MouseMoved)
                return true;
            else
                return false;
        }
        else
            throw 1;
    }
    catch (int error)
    {
        if (error == 1)
            cout << "No button" << endl;
        return false;
    }
}
bool Buttons::IsClicked()
{
    try
    {
        if (Button != nullptr)
        {
            if (ShapeContainsMouse() && GameBoard->Event.type == sf::Event::MouseButtonPressed)
                return true;
            else
                return false;
        }
        else
            throw 1;
    }
    catch (int error)
    {
        if (error == 1)
            cout << "No button" << endl;
        return false;
    }
}
bool Buttons::IsReleased()
{
    try
    {
        if (Button != nullptr)
        {
            if (ShapeContainsMouse() && GameBoard->Event.type == sf::Event::MouseButtonReleased)
                return true;
            else
                return false;
        }
        else
            throw 1;
    }
    catch (int error)
    {
        if (error == 1)
            cout << "No button" << endl;
        return false;
    }
}
Buttons::~Buttons()
{
    delete Button;
    delete ButtonText;
    GameBoard = nullptr; // board is pointer to an object that may be reused, do not delete it
}