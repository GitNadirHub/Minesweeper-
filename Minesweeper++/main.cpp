#include "begginerMode.h"
using namespace sf;

RenderWindow window(VideoMode({ 288, 450 }), "Minesweeper++");

int main()
{
    state = Ongoing;
    level = Beginner;
    while (1)
    {
        switch (level)
        {
        case Beginner:
            switch (state)
            {
            case Ongoing: beginnerMode(); break;
            case Win: begWin(); break;
            case Loss: begLose(); break;
            }
            break;
        }
    }
}