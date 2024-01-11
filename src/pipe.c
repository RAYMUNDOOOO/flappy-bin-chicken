#include <stdlib.h>
#include "raylib.h"
#include "pipe.h"

// CONSTANTS
#define PIPE_DX 480
#define PIPE_DY 150
#define PIPE_W 80
#define PIPE_H GetScreenHeight()
#define PIPE_MS 520

// DECLARATIONS
void Move(Pipe* pipes, int numPipes, const float DELTA_TIME);
void SetRandYPos(Pipe* p, const int SCREEN_H);
void ResetPipeX(Pipe* p);

// DEFINITIONS
void InitPipe(Pipe* pipes, int numPipes) 
{
	if (numPipes > 0)
	{
		const int MIDDLE_SCREEN_Y = GetScreenHeight() / 2; 
		const int MIDDLE_SCREEN_X = GetScreenWidth() / 2;

		for (int i = 0; i < numPipes; ++i)
		{
			// Spawn position starts from end of screen and then translates depending on which pipe we're spawning.
			const int X = MIDDLE_SCREEN_X + (i * (PIPE_W + PIPE_DX));

			pipes[i].upperBody.x = X;
			pipes[i].upperBody.width = PIPE_W;
			pipes[i].upperBody.height = PIPE_H;

			pipes[i].lowerBody.x = X;
			pipes[i].lowerBody.width = PIPE_W;
			pipes[i].lowerBody.height = PIPE_H;

			pipes[i].scoreBody.x = X + (PIPE_W / 2);
			pipes[i].scoreBody.width = 10;
			pipes[i].scoreBody.height = PIPE_DY;

			SetRandYPos(&pipes[i], GetScreenHeight());
		}
	}
}				

void TickPipe(Pipe* pipes, int numPipes, const float DELTA_TIME)
{
	Move(pipes, numPipes, DELTA_TIME);
}

void DrawPipe(Pipe* pipes, int numPipes)
{
	if (numPipes > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			DrawRectanglePro(pipes[i].upperBody, (Vector2){ 0, 0 }, 0, BLACK);
			DrawRectanglePro(pipes[i].lowerBody, (Vector2){ 0, 0 }, 0, BLACK);
		}
	}
}

int GetNumPipes(const int SCREEN_W)
{
	return (SCREEN_W / (PIPE_W + PIPE_DX)) + 2;
}

void Move(Pipe* pipes, int numPipes, const float DELTA_TIME)
{
	if (numPipes > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			pipes[i].upperBody.x -= PIPE_MS * DELTA_TIME;
			pipes[i].lowerBody.x -= PIPE_MS * DELTA_TIME;
			pipes[i].scoreBody.x -= PIPE_MS * DELTA_TIME;

			if (pipes[i].upperBody.x <= -(PIPE_W + PIPE_W + PIPE_DX))
			{
				ResetPipeX(&pipes[i]);
				SetRandYPos(&pipes[i], GetScreenHeight());
			}
		}
	}
}

/*
 * TODO: In the future I would like this to be based on the position of the previous pipe
 * so we can avoid pipes spawning too far away from each other and being impossible
 * for the player to reach.
 */
void SetRandYPos(Pipe* p, const int SCREEN_H)
{
	const int MAX_POS_Y = (SCREEN_H / 2) + (SCREEN_H * 0.3);
	const int MIN_POS_Y = (SCREEN_H / 2) - (SCREEN_H * 0.3);

	const int RAND_Y = MIN_POS_Y + (rand() % (MAX_POS_Y - MIN_POS_Y));
	p->upperBody.y = RAND_Y - SCREEN_H;
	p->lowerBody.y = RAND_Y + PIPE_DY;
	p->scoreBody.y = RAND_Y;
}

void ResetPipeX(Pipe* p)
{
	p->upperBody.x = GetScreenWidth();
	p->lowerBody.x = GetScreenWidth();
	p->scoreBody.x = GetScreenWidth() + (PIPE_W / 2);
}
