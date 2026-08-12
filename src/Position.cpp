#include <raylib.h>
#include "grid.h"
#include "Block.h"
#include "Position.h"


Position::Position(int row, int col)
{
    this->row = row;
    this->col = col;
}
