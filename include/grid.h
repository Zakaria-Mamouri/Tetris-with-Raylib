#pragma once
#include <vector>
#include<raylib.h>
#include "Block.h"


class Grid
{
    public:
        Grid();
        void initialize();
        void Print();
        int grid [20][10];
        void Draw();
        bool isCellOutside(int row, int col);
        bool isCellEmpty(int row, int col);
        int clearFullRows();
    private:
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> Colors;
        bool isRowComplete(int row);
        void clearRow(int row);
        void moveRowDown(int row, int numRows);
};

