#include <raylib.h>
#include "grid.h"
#include "Block.h"
#include "Position.h"
#include "colors.h"


Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}


void Block::Draw(int xOffset, int yOffset)
{
    std::vector<Position> tiles = GetCellPositions();
    for(Position item: tiles)
    {
        DrawRectangle(item.col*cellSize + xOffset, item.row*cellSize + yOffset, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles)
    {
        Position newPos(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;

}


void Block::Rotate()
{
    if(rotationState == cells.size() - 1)
    {
        rotationState = 0;
    }
    else
    {
        rotationState ++;
    }
}


void Block::undoRotate()
{
        if(rotationState == 0)
        {
            rotationState = cells.size() - 1;
        }
        else{
            rotationState --;
        }
}

