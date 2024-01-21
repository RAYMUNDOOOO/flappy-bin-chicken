#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "main.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

int score = 0;
int numPipes = 0;
static Bird* bird = NULL;
static Pipe* pipes = NULL;
Sound scoreSfx;
Sound collisionSfx;
Sound gameOverSfx;

void QueryCollisions(const Bird* bird, Pipe* pipes);
void AddScore(const int value);

void InitGame()
{
	bird = (Bird*)malloc(sizeof(Bird));
	InitBird(bird);

	numPipes = GetNumPipes(GetScreenWidth());
	pipes = (Pipe*)malloc(numPipes * sizeof(Pipe));
	InitPipe(pipes, numPipes);

    // Audio configuration
    if (IsAudioDeviceReady())
    {
        scoreSfx = LoadSound("../res/audio/score.wav");
        collisionSfx = LoadSound("../res/audio/collision.wav");
        gameOverSfx = LoadSound("../res/audio/gameOver.wav");
        printf("Loaded game sounds!\n");
    }
}

void TickGame(const float DELTA_TIME)
{
	TickBird(bird, DELTA_TIME);
	TickPipe(pipes, numPipes, DELTA_TIME);
	QueryCollisions(bird, pipes);
}

void DrawGame()
{
	DrawPipe(pipes, numPipes);
	DrawBird(bird);
}

void CleanGame()
{
	free(bird);
	bird = NULL;
	free(pipes);
	pipes = NULL;
}

void QueryCollisions(const Bird* bird, Pipe* pipes)
{
	if (numPipes > 0)
	{
		for (int i = 0; i < numPipes; i++)
		{
            if (CheckCollisionRecs(bird->body, pipes[i].upperBody) || 
                CheckCollisionRecs(bird->body, pipes[i].lowerBody))
            {
                PlaySound(collisionSfx);
                DisableInput();
                DisablePipeMovement();
            }

			if (CheckCollisionRecs(bird->body, pipes[i].scoreBody)) 
			{	
                PlaySound(scoreSfx);
				AddScore(1);
				pipes[i].scoreBody.y = 0;
			}
		}
	}

    // Present GAME OVER menu when bird falls to bottom of screen.
    if (bird->body.y <= 0 || bird->body.y >= GetScreenHeight())
    {
        PlaySound(gameOverSfx);
        GameOver();
    }
}

void AddScore(const int value)
{
	score += value;
}

int GetScore()
{
	return score; 
}

void RestartGame()
{
    score = 0;
	InitBird(bird);
    InitPipe(pipes, numPipes);
    EnableInput();
    EnablePipeMovement();
    SetGameRunning();
}
