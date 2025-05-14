#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define MINE 8


using namespace sf;
RenderWindow window(VideoMode({ 288, 450 }), "Minesweeper++");

Texture t_cellBg("assets/sprites/cellBg.png");
Sprite cellBg(t_cellBg);


struct cell
{
    int val=0;
    bool visible=0;
};



void displayWindow()
{
	while (window.isOpen())
	{
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
	}
}


void initBeginnerMode()
{
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    cell grid[9][9];

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cellBg.setPosition({ 32.f * i, 32.f*j });
                window.draw(cellBg);
            }
        }
        window.display();
    }
}

int main()
{
    initBeginnerMode();

}