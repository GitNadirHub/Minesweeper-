#include "grid.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <utility>
#include <unordered_set>

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

/*
    1 2 - 0         1 1 - 3/2
    3 4 - 1
    5 6 - 2

*/

std::pair<int, int> getCoordinates(int x, int cols, int rows)
{
    int row = x / cols;
    int col = x % cols;

    return { row, col }; //Returns i, j
}

int flattenCoordinates(int row, int col, int cols)
{
    return row * cols + col;
}

void genRandomMines(int i_exception, int j_exception, cell grid[][9], int rows, int cols)
{
    int n = 15;

    int a[81], asize=0;
    
    std::unordered_set<int> exceptions;

    exceptions.insert(flattenCoordinates(i_exception, j_exception, cols));
    
    int dirs[8][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (int i = 0; i < 8; i++)
    {
        int ni = i_exception + dirs[i][0];
        int nj = j_exception + dirs[i][1];
        if (isValid(ni, nj))
            exceptions.insert(flattenCoordinates(ni, nj, cols));
    }

    for (int i = 0; i < 81; i++)
    {
        if (!exceptions.count(i))
            a[asize++] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(a, a + asize, std::default_random_engine(seed));

    for (int ii = 0; ii<n; ii++)
    {
        auto p = getCoordinates(a[ii], cols, rows);
        int i = p.first, j = p.second;

        addCnt(i + 1, j, grid);
        addCnt(i, j + 1, grid);
        addCnt(i - 1, j, grid);
        addCnt(i, j - 1, grid);

        addCnt(i + 1, j + 1, grid);
        addCnt(i - 1, j - 1, grid);
        addCnt(i + 1, j - 1, grid);
        addCnt(i - 1, j + 1, grid);

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