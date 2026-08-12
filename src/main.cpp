#include <raylib.h>
#include "game.h"
#include <iostream>
#include <ctime>
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;
bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;

    }
    return false;
}


Font font = LoadFontEx("assets/Relidux.otf", 64, 0, 0);

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);
    Game game;



    while(WindowShouldClose() == false)
    {
        //UpdateMusicStream(game.music);
        game.HandleInput();
        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "score", {350, 20}, 40, 2, WHITE);
        DrawRectangleRounded({330, 70, 150, 60}, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 40, 2);



        DrawTextEx(font, scoreText, {330 + (150-textSize.x)/2, 80}, 40, 2, WHITE);
        DrawTextEx(font, "next", {365, 175}, 40, 2, WHITE);
        DrawRectangleRounded({330, 225, 150, 150}, 0.3, 6, lightBlue);
        if(game.gameOver)
        {
            DrawTextEx(font, "Game\nOver", {360, 440}, 40, 2, WHITE);
        }
        game.Draw();
        if(eventTriggered(0.3))
        {
            game.MoveBlockDown();
        }

        EndDrawing();
    }

    CloseWindow();
}
