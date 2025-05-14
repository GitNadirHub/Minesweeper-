#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>

#define MINE 8


using namespace sf;
RenderWindow window(VideoMode({ 288, 450 }), "Minesweeper++");

Texture t_cellBg("assets/sprites/cellBg.png");
Sprite cellBg(t_cellBg);

Texture t_cellCover("assets/sprites/cellCover.png");
Sprite cellCover(t_cellCover);

Texture t_cellMine("assets/sprites/cellMine.png");
Sprite cellMine(t_cellMine);

Texture t_cell1("assets/sprites/cell1.png");
Sprite cell1(t_cell1);

Texture t_cell2("assets/sprites/cell2.png");
Sprite cell2(t_cell2);

Texture t_cellFlag("assets/sprites/cellFlag.png");
Sprite cellFlag(t_cellFlag);

struct cell
{
    int val = 0;
    bool visible = 0;
    bool flagged = 0;
};

void fill(int i, int j, cell grid[][9])
{
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
        return;
    if (grid[i][j].visible || grid[i][j].val == MINE)
        return;
    grid[i][j].visible = 1;
    if (grid[i][j].val != 0)
        return;

    fill(i + 1, j, grid);
    fill(i, j + 1, grid);
    fill(i - 1, j, grid);
    fill(i, j - 1, grid);

    fill(i + 1, j + 1, grid);
    fill(i + 1, j - 1, grid);
    fill(i - 1, j + 1, grid);
    fill(i - 1, j - 1, grid);
}


void addCnt(int i, int j, cell grid[][9])
{
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
        return;
    if (grid[i][j].val == MINE)
        return;
    grid[i][j].val++;
}


void genRandomMines(int i_exception, int j_exception, cell grid[][9])
{
    int n = 10;
    while (n--)
    {
        int i = rand() % 9;
        int j = rand() % 9;

        if (i == i_exception && j == j_exception)
        {
            i++, i%=9;
        }

        if (grid[i][j].val != MINE)
        {
            addCnt(i + 1, j, grid);
            addCnt(i, j + 1, grid);
            addCnt(i - 1, j, grid);
            addCnt(i, j - 1, grid);

            addCnt(i + 1, j + 1, grid);
            addCnt(i - 1, j - 1, grid);
            addCnt(i + 1, j - 1, grid);
            addCnt(i - 1, j + 1, grid);
        }

        grid[i][j].val = MINE;
    }
}

bool isValid(int i, int j)
{
    return (i >= 0 && i < 9 && j >= 0 && j < 9);
}

bool isValidFlagged(int i, int j, cell grid[][9])
{
    if (!isValid(i, j))
        return false;
    if (grid[i][j].flagged)
        return true;
    return false;
}

int adjacentMinesCount(int i, int j, cell grid[][9])
{
    int cnt = 0;
    cnt += isValidFlagged(i, j+1, grid);
    cnt += isValidFlagged(i+1, j, grid);
    cnt += isValidFlagged(i-1, j, grid);
    cnt += isValidFlagged(i, j-1, grid);
    
    cnt += isValidFlagged(i+1, j+1, grid);
    cnt += isValidFlagged(i-1, j-1, grid);
    cnt += isValidFlagged(i+1, j-1, grid);
    cnt += isValidFlagged(i-1, j+1, grid);

    return cnt;
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
                        else if (grid[y][x].visible == 1)
                        {
                            if (adjacentMinesCount(y, x, grid) == grid[y][x].val)
                            {
                                if (isValid(y+1, x) && grid[y+1][x].val!=MINE) grid[y+1][x].visible = 1;
                                if (isValid(y, x+1) && grid[y][x+1].val!=MINE) grid[y][x+1].visible = 1;
                                if (isValid(y-1, x) && grid[y-1][x].val!=MINE) grid[y-1][x].visible = 1;
                                if (isValid(y, x-1) && grid[y][x-1].val!=MINE) grid[y][x-1].visible = 1;

                                if (isValid(y + 1, x + 1) && grid[y+1][x + 1].val != MINE) grid[y+1][x + 1].visible = 1;
                                if (isValid(y - 1, x - 1) && grid[y-1][x - 1].val != MINE) grid[y-1][x - 1].visible = 1;
                                if (isValid(y + 1, x - 1) && grid[y+1][x - 1].val != MINE) grid[y+1][x - 1].visible = 1;
                                if (isValid(y - 1, x + 1) && grid[y-1][x + 1].val != MINE) grid[y-1][x + 1].visible = 1;

                            }
                        }
                        grid[y][x].visible = 1, grid[y][x].flagged=0;
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
            }
        }
        window.display();
    }
}

int main()
{
    beginnerMode();
}