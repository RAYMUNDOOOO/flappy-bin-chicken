#include "raylib.h"
#include "main.h"
#include "menus.h"
#include "game.h"
#include <stdio.h>

// Screen attributes.
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

typedef enum 
{
	MAIN_MENU,
	RUNNING,
	PAUSED,
	GAME_OVER,
	QUITTING
} ApplicationState;
ApplicationState applicationState = MAIN_MENU;

Sound buttonSfx;

// Declarations.
void SetupWindow();
void SetupAudio();
void DrawScore();

int main(void)
{
	SetupWindow();
    SetupAudio();
    if (IsAudioDeviceReady()) buttonSfx = LoadSound("../res/audio/button.wav");

	while (!WindowShouldClose() && applicationState != QUITTING)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(10, 10);

		switch (applicationState)
		{
			case MAIN_MENU:
			{
				// InitGame();
                DrawPanel();
                DrawLabel("FLAPPY BIN CHICKEN");

                if (DrawStartButton())
                {
                    PlaySound(buttonSfx);
                    InitGame();
                    SetGameRunning();
                }

                if (DrawQuitButton()) 
                {
                    SetGameQuitting();
                    PlaySound(buttonSfx);
                }
			} break;

			case RUNNING:
			{
                if (IsKeyPressed(KEY_ESCAPE)) SetGamePaused();
				TickGame(GetFrameTime());
				DrawGame();
		        DrawScore();
			} break;

			case PAUSED:
			{
                if (IsKeyPressed(KEY_ESCAPE)) SetGameRunning();

                DrawGame();
                DrawPanel();
                DrawLabel("PAUSED");

                if (DrawResumeButton()) 
                {
                    SetGameRunning();
                    PlaySound(buttonSfx);
                }

                if (DrawQuitButton())
                {
                    SetGameQuitting();
                    PlaySound(buttonSfx);
                }

		        DrawScore();
			} break;

			case GAME_OVER:
			{
                DrawGame();
                DrawPanel();
                DrawLabel("GAME OVER");

                if (DrawPlayAgainButton())
                {
                    RestartGame();
                    PlaySound(buttonSfx);
                }

                if (DrawQuitButton())
                {
                    applicationState = QUITTING;
                    PlaySound(buttonSfx);
                }

		        DrawScore();
			} break;

            case QUITTING:
            {
	            CleanGame();
            } break;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void SetupWindow()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
    InitGui();
	SetExitKey(0);
	SetTargetFPS(144);
}

void SetupAudio()
{
    InitAudioDevice();
}

void DrawScore()
{
	char scoreStr[8];
	sprintf(scoreStr, "%d", GetScore());
	DrawText(scoreStr, GetScreenWidth() / 2, GetScreenHeight() * 0.1, 32, BLACK);
}

void SetGamePaused()
{
    applicationState = PAUSED;
}

void SetGameRunning()
{
    applicationState = RUNNING;
}

void GameOver()
{
    applicationState = GAME_OVER; 
}

void SetGameQuitting()
{
    applicationState = QUITTING;
}
