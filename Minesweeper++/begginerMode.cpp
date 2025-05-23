#include "begginerMode.h"
#include <sstream>
#include <iomanip>

using namespace sf;

auto bgColor = sf::Color{ 120, 152, 193, 255 };

cell grid[9][9];

int initialMineCount = 15;
int mineCount = initialMineCount;

cell* fault = nullptr; //used for loss screen

Text timeText(digFont);
Text mineText(digFont);


//Abdullah my beloved <3

void abdullahInit(Sprite &sprite)
{
    float winMidX = (window.getSize().x) / 2;
    sprite.setScale({ 2.f, 2.f });
    float imgWidth = 64.f;
    sprite.setPosition({ winMidX - imgWidth / 2, extraH / 2 });
}

void binit()
{
    mineCount = 15;
    state = Ongoing;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j] = {0, 0, 0};
}



void begWin()
{
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    const int extraH = 160;

    abdullahInit(cool);
    mineText.setString("000");

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


        window.draw(cool);

        display.setPosition({ 8.f, smile.getPosition().y + 8.f });
        mineText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        display.setPosition({ window.getSize().x - t_display.getSize().x - 8.f , smile.getPosition().y + 8.f });
        timeText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        window.draw(mineText);
        window.draw(timeText);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (grid[i][j].val == 0)
                {
                    cellBg.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cellBg);
                }
                else if (grid[i][j].val == MINE)
                {
                    cellFlag.setPosition({ 32.f * j, 32.f * i + extraH });
                    window.draw(cellFlag);
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


void begLose()
{
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");
    const int extraH = 160;

    abdullahInit(sad);

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


        window.draw(sad);

        display.setPosition({ 8.f, smile.getPosition().y + 8.f });
        mineText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        display.setPosition({ window.getSize().x - t_display.getSize().x - 8.f , smile.getPosition().y + 8.f });
        timeText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        window.draw(mineText);
        window.draw(timeText);

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
    window.setSize({ 288, 450 });
    window.setTitle("Minesweeper++ - Beginner");

    bool gameStarted = 0;
    fault = nullptr;

    abdullahInit(smile);

    Clock clock;

    timeText.setCharacterSize(60);
    mineText.setCharacterSize(60);

    timeText.setString("000");

    mineText.setString(fillNumericString(mineCount));

    int counter = 1;
    float updateInterval = 1.0f;

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
                            genRandomMines(y, x, grid, 9, 9, mineCount);
                            fill(y, x, grid);
                        }
                        else if (grid[y][x].val == 0)
                        {
                            fill(y, x, grid);
                        }
                        else if (grid[y][x].val == MINE)
                        {
                            state = Loss;
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
                                            state = Loss;
                                            return;
                                        }
                                        if (grid[ny][nx].val == 0)
                                            fill(ny, nx, grid);
                                        grid[ny][nx].visible = 1;
                                    }
                                }

                            }
                        }
                        grid[y][x].visible = 1, grid[y][x].flagged = 0;
                    }
                }
                else if (mouseButtonPressed->button == sf::Mouse::Button::Right && gameStarted)
                {
                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;

                    y -= extraH;

                    x /= 32, y /= 32;
                    if (isValid(y, x) && !grid[y][x].visible)
                    {
                        grid[y][x].flagged = !grid[y][x].flagged;
                        mineCount += (-1 * grid[y][x].flagged) * 2 + 1;
                        mineText.setString(fillNumericString(mineCount)); // adds/subtracts 1
                    }
                }
            }
        }
        
        
        if (gameStarted && clock.getElapsedTime().asSeconds() >= updateInterval)
        {
            clock.restart();

            if (counter <= 999)
            {
                timeText.setString(fillNumericString(counter++));
            }
            else
            {
                timeText.setString(":3");
            }
        }
        
        window.clear(bgColor);

        window.draw(smile);

        display.setPosition({8.f, smile.getPosition().y+8.f});
        mineText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        display.setPosition({window.getSize().x - t_display.getSize().x - 8.f , smile.getPosition().y + 8.f});
        timeText.setPosition({ display.getPosition().x + 10, display.getPosition().y - 16 });
        window.draw(display);

        window.draw(mineText);
        window.draw(timeText);

        unsigned total = 0;

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
                else
                {
                    total++;
                    if (grid[i][j].val == 0)
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
        }
        if (total == 9 * 9 - initialMineCount)
        {
            state = Win;
            return;
        }
        window.display();
    }
}
