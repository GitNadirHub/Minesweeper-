#include "begginerMode.h"
using namespace sf;

sf::RenderWindow window(sf::VideoMode({ 288, 450 }), "Minesweeper++");


int main()
{
    state = "beg";
    while (1)
    {
        if (state == "beg")
        {
            beginnerMode();
        }
        else if (state == "loss")
        {
            lose();
        }
    }
}