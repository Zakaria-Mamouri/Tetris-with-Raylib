#pragma once
#include "grid.h"
#include <vector>
#include "Blocks.cpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void MoveBlockDown();
        void HandleInput();
        bool gameOver;
        int score;
        Music music;


    private:
        Grid grid;
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void MoveBlockLeft();
        void MoveBlockRight();
        void RotateBlock();
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        bool isBlockOutside();
        bool isBlockEmpty();
        void lockBlock();
        void reset();
        void updateScore(int linesCleared, int moveDownPoints);
        Sound rotateSound;
        Sound clearSound;



};
