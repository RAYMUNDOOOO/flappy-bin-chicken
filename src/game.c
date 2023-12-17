#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

int score = 0;
int numPipes = 0;
static Bird* bird = NULL;
static Pipe* pipes = NULL;

void QueryCollisions(const Bird* bird, const Pipe* pipes);
void AddScore(const int value);

void InitGame()
{
	bird = (Bird*)malloc(sizeof(Bird));
	InitBird(bird);

	numPipes = GetNumPipes(GetScreenWidth());
	pipes = (Pipe*)malloc(numPipes * sizeof(Pipe));
	InitPipe(pipes, numPipes);
}

void TickGame(const float DELTA_TIME)
{
	TickBird(bird, DELTA_TIME);
	TickPipe(pipes, numPipes, DELTA_TIME);
	QueryCollisions(bird, pipes);
}

void DrawGame()
{
	DrawBird(bird);
	DrawPipe(pipes, numPipes);
}

void CleanGame()
{
	free(bird);
	bird = NULL;
	free(pipes);
	pipes = NULL;
}

void QueryCollisions(const Bird* bird, const Pipe* pipes)
{
	if (numPipes > 0)
	{
		for (int i = 0; i < numPipes; i++)
		{
			if (CheckCollisionRecs(bird->body, pipes[i].upperBody)) printf("Collision detected with upper body.\n");
			if (CheckCollisionRecs(bird->body, pipes[i].lowerBody)) printf("Collision detected with lower body.\n");
			if (CheckCollisionRecs(bird->body, pipes[i].scoreBody)) 
			{
				AddScore(1);	
			}
		}
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
