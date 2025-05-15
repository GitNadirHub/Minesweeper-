#include "begginerMode.h"
using namespace sf;

void lose(cell grid[][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j].visible = 1;

}

void beginnerMode()
{
    srand(time(0));
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    cell grid[9][9];
    const int extraH = 160;

    bool gameStarted = 0;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;

                    y -= extraH;

                    x /= 32, y /= 32;

                    //std::cout << x << ' ' << y << std::endl;
                    if (isValid(y, x))
                    {
                        if (!gameStarted)
                        {
                            gameStarted = 1;
                            genRandomMines(y, x, grid);
                            fill(y, x, grid);
                        }
                        else if (grid[y][x].val == 0)
                        {
                            fill(y, x, grid);
                        }
                        else if (grid[y][x].val == MINE)
                        {
                            lose(grid);
                        }
                        else if (grid[y][x].visible == 1)
                        {
                            if (adjacentMinesCount(y, x, grid) >= grid[y][x].val)
                            {
                                if (isValid(y + 1, x) && grid[y + 1][x].val != MINE) grid[y + 1][x].visible = 1;
                                if (isValid(y, x + 1) && grid[y][x + 1].val != MINE) grid[y][x + 1].visible = 1;
                                if (isValid(y - 1, x) && grid[y - 1][x].val != MINE) grid[y - 1][x].visible = 1;
                                if (isValid(y, x - 1) && grid[y][x - 1].val != MINE) grid[y][x - 1].visible = 1;

                                if (isValid(y + 1, x + 1) && grid[y + 1][x + 1].val != MINE) grid[y + 1][x + 1].visible = 1;
                                if (isValid(y - 1, x - 1) && grid[y - 1][x - 1].val != MINE) grid[y - 1][x - 1].visible = 1;
                                if (isValid(y + 1, x - 1) && grid[y + 1][x - 1].val != MINE) grid[y + 1][x - 1].visible = 1;
                                if (isValid(y - 1, x + 1) && grid[y - 1][x + 1].val != MINE) grid[y - 1][x + 1].visible = 1;

                            }
                        }
                        grid[y][x].visible = 1, grid[y][x].flagged = 0;
                    }
                }
                else if (mouseButtonPressed->button == sf::Mouse::Button::Right)
                {
                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;

                    y -= extraH;

                    x /= 32, y /= 32;
                    if (isValid(y, x) && !grid[y][x].visible)
                    {
                        grid[y][x].flagged = !grid[y][x].flagged;
                    }
                }
            }
        }
        window.clear();
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (!grid[i][j].visible)
                {
                    if (grid[i][j].flagged)
                    {
                        cellFlag.setPosition({ 32.f * j, 32.f * i + extraH });
                        window.draw(cellFlag);
                    }
                    else
                    {
                        cellCover.setPosition({ 32.f * j, 32.f * i + extraH });
                        window.draw(cellCover);
                    }
                }
                else if (grid[i][j].val == 0)
                {
                    cellBg.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cellBg);
                }
                else if (grid[i][j].val == MINE)
                {
                    cellMine.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cellMine);
                }
                else if (grid[i][j].val == 1)
                {
                    cell1.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cell1);
                }
                else if (grid[i][j].val == 2)
                {
                    cell2.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cell2);
                }
                else if (grid[i][j].val == 3)
                {
                    cell3.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cell3);
                }
            }
        }
        window.display();
    }
}
