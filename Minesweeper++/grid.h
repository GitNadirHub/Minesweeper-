#pragma once
#include "assets.h"
#define MINE 8

void fill(int i, int j, cell grid[][9]);
void addCnt(int i, int j, cell grid[][9]);
void genRandomMines(int i_exception, int j_exception, cell grid[][9], int rows, int cols);
bool isValid(int i, int j), isValidFlagged(int i, int j, cell grid[][9]);
int adjacentMinesCount(int i, int j, cell grid[][9]);