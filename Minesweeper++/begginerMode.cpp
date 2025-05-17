#include "begginerMode.h"
using namespace sf;

auto bgColor = sf::Color{ 120, 152, 193, 255 };

cell grid[9][9];

cell* fault = nullptr;

void binit()
{
    state = "beg";
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j] = {0, 0, 0};
}

void lose()
{
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    const int extraH = 160;


    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j].visible = 1;

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
                    binit();
                    return;
                }
            }
        }
        window.clear(bgColor);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (&grid[i][j] == fault)
                {
                    cellMineBad.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cellMineBad);
                    continue;
                }
                if (grid[i][j].flagged)
                {
                    if (grid[i][j].val == MINE)
                    {
                        cellFlag.setPosition({ 32.f * j, 32.f * i + extraH });
                        window.draw(cellFlag);
                    }
                    else
                    {
                        cellFlagBad.setPosition({ 32.f * j, 32.f * i + extraH });
                        window.draw(cellFlagBad);
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
                else if (grid[i][j].val == 4)
                {
                    cell4.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cell4);
                }
            }
        }
        window.display();
    }
}

void beginnerMode()
{
    srand(time(0));
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    const int extraH = 160;

    bool gameStarted = 0;
    fault = nullptr;

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
                    if (isValid(y, x) && !grid[y][x].flagged)
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
                            state = "loss";
                            fault = &grid[y][x];
                            return;
                        }
                        else if (grid[y][x].visible == 1)
                        {
                            if (adjacentMinesCount(y, x, grid) >= grid[y][x].val)
                            {
                                int dirs[8][2] = {
                                    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
                                    {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
                                };

                                for (int i = 0; i < 8; ++i)
                                {
                                    int ny = y + dirs[i][0];
                                    int nx = x + dirs[i][1];

                                    if (isValid(ny, nx) && grid[ny][nx].val != MINE)
                                    {
                                        if (grid[ny][nx].flagged)
                                        {
                                            state = "loss";
                                            return;
                                        }
                                        grid[ny][nx].visible = 1;
                                    }
                                }

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
        window.clear(bgColor);
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
                else if (grid[i][j].val == 4)
                {
                    cell4.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cell4);
                }
            }
        }
        window.display();
    }
}
