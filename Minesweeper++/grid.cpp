#include "grid.h"


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
            i++, i %= 9;
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
    cnt += isValidFlagged(i, j + 1, grid);
    cnt += isValidFlagged(i + 1, j, grid);
    cnt += isValidFlagged(i - 1, j, grid);
    cnt += isValidFlagged(i, j - 1, grid);

    cnt += isValidFlagged(i + 1, j + 1, grid);
    cnt += isValidFlagged(i - 1, j - 1, grid);
    cnt += isValidFlagged(i + 1, j - 1, grid);
    cnt += isValidFlagged(i - 1, j + 1, grid);

    return cnt;
}