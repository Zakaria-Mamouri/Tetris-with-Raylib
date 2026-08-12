#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include <raylib.h>


class Block
{
    public:
        Block();
        int id;
        std::map<int, std::vector<Position>> cells;
        void Draw(int xOffset, int yOffset);
        void Move(int rowOffset, int colOffset);
        std::vector<Position> GetCellPositions();
        void Rotate();
        void undoRotate();
    private:
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
        int rowOffset;
        int colOffset;

};


