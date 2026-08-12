#include "game.h"
#include <random>


Game::Game()
{
    gameOver = false;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock  = GetRandomBlock();
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("assets/sound/bgmusic.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("assets/sound/rotate.mp3");
    clearSound = LoadSound("assets/sound/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}


std::vector<Block> Game::GetAllBlocks()
{
    return {Lblock(), Jblock(), Tblock(), Iblock(), Oblock(), Sblock(), Zblock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch(nextBlock.id)
    {
    case 4:
        nextBlock.Draw(210 + (150 - 29*3)/2 + 14, 225 + (150 - 29*3)/2 + 29);
        break;
    case 5:
        nextBlock.Draw(210 + (150 - 29*3)/2 + 15, 225 + (150 - 29*3)/2 + 15);
        break;
    default:
        nextBlock.Draw(210 + (150 - 29*3)/2, 225 + (150 - 29*3)/2);
    }
}


void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0)
    {
        gameOver = false;
        reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        updateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
    }
}


void Game::MoveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0, -1);
        if(isBlockOutside() || !isBlockEmpty())
        {
            bool a = !isBlockEmpty();
            currentBlock.Move(0, 1);
            if(a)
            {
                lockBlock();
            }

        }
    }

}

void Game::MoveBlockRight()
{
{
    if(!gameOver)
    {
        currentBlock.Move(0, 1);
        if(isBlockOutside() || !isBlockEmpty())
        {
            bool a = !isBlockEmpty();
            currentBlock.Move(0, -1);
            if(a)
            {
                lockBlock();
            }

        }
    }

}
}

void Game::MoveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1,0);
        if(isBlockOutside() || !isBlockEmpty())
        {

            currentBlock.Move(-1,0);
            lockBlock();

        }
    }

}


void Game::RotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(isBlockOutside() || !isBlockEmpty())
        {
            currentBlock.undoRotate();
            lockBlock();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }

}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(grid.isCellOutside(item.row, item.col))
        {
            return true;
            break;
        }
    }
    return false;
}

void Game::lockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(!isBlockEmpty())
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int clearedRows = grid.clearFullRows();
    if(clearedRows > 0)
    {
        PlaySound(clearSound);
    }
    updateScore(clearedRows, 0);

}


bool Game::isBlockEmpty()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(!grid.isCellEmpty(item.row, item.col))
        {
            return false;
        }
    }
    return true;
}


void Game::reset()
{
    grid.initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
    score += 100 * linesCleared;

    score += moveDownPoints;
}

