#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "raylib.h"
#include <stdlib.h>

int numPipes = 0;
static Bird* bird = NULL;
static Pipe* pipes = NULL;

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
