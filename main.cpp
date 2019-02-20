#include "MainMenu.h"
#include "Snake.h"
int main()
{
    Board *bord = new Board("Snake", 1000, 1060); // menu bar height summed up so they are perfect squares
    MainMenu menu(bord);
    int status = menu.Loop();
    if (status == 1)
    {
        cout << "Play\n";
        Snake snake(bord);
        int status = snake.Loop();
        if (status == 0)
            cout << "Quit\n";
        else if (status == 1)
            cout << "Go back\n";
        else if (status == 2)
            cout << "Lost\n";
        else if(status == 3)
            cout << "Won!\n";  
    }
    else if (status == 0)
        cout << "Quit\n";
}