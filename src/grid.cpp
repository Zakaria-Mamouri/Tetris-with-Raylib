#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "Block.h"
#include "Position.h"
#include "colors.h"
#include "game.h"

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initialize();
    Colors = GetCellColors();
}

void Grid::initialize()
{
    for(int row= 0; row< numRows; row++){
        for(int col= 0; col< numCols; col++){
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row= 0; row< numRows; row++){
        for(int col= 0; col< numCols; col++){
            std::cout << grid[row][col]<< " ";
        }
        std::cout <<std::endl;
    }
}


void Grid::Draw()
{
    for(int row = 0; row< numRows; row++)
    {
        for(int col= 0; col< numCols; col++)
        {
            int CellValue = grid[row][col];
            DrawRectangle(col*cellSize + 1 + 10, row*cellSize + 1 + 10, cellSize -1, cellSize -1, Colors[CellValue]);
        }

    }
}

bool Grid::isCellOutside(int row, int col)
{
    if(row < 0 || row >= numRows || col <0 || col >= numCols)
    {
        return true;
    }
    return false;
}




bool Grid::isCellEmpty(int row, int col)
{
    if(grid[row][col] == 0)
    {
        return true;
    }
    return false;
}


bool Grid::isRowComplete(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        if(grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}


void Grid::clearRow(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}


void Grid::moveRowDown(int row, int numRows)
{
    for(int col; col < numCols; col++)
    {
        grid[row + numRows][col] = grid[row][col];
    }
}

int Grid::clearFullRows()
{
    int completed = 0;
    for(int row = numRows - 1; row >= 0; row--)
    {
        if(isRowComplete(row))
        {
            clearRow(row);
            completed++;
        }
        else if(completed > 0)
        {
            moveRowDown(row, completed);
        }
    }
    return completed;


}
