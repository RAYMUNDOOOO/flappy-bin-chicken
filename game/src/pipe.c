#include "raylib.h"
#include "pipe.h"

// CONSTANTS
#define PIPE_DX 180
#define PIPE_DY 150
#define PIPE_W 80
#define PIPE_H GetScreenHeight()
#define PIPE_MS 120

// DECLARATIONS
void Move(Pipe pipes[], const int NUM_PIPES, const float DELTA_TIME);
void SetRandYPos(Pipe* p, const int SCREEN_H, const int SCREEN_W);
void ResetPipeX(Pipe* p);

// DEFINITIONS
void Init(Pipe pipes[], const int NUM_PIPES) 
{
	if (NUM_PIPES > 0)
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

			pipes[i].scoreBody.x = X;
			pipes[i].scoreBody.width = PIPE_W;
			pipes[i].scoreBody.height = PIPE_H;

			SetRandYPos(Pipe* pipe, const int SCREEN_H, const int SCREEN_W);
		}
	}
}				

void Tick(Pipe pipes[], const float DELTA_TIME)
{
	Move(pipes, sizeof(pipes) / sizeof(pipes[0]), DELTA_TIME);
}

void Draw(Pipe pipes[])
{
	if (sizeof(*pipes) > 0)
	{
		for (int i = 0; i < sizeof(pipes) / sizeof(pipes[0]); ++i)
		{
			DrawRectanglePro(pipes[i].upperBody, (Vector2){ 0, 0 }, 0, RAYWHITE);
			DrawRectanglePro(pipes[i].lowerBody, (Vector2){ 0, 0 }, 0, RAYWHITE);
		}
	}
}

int GetNumPipes(const int SCREEN_W)
{
	return (SCREEN_W / (PIPE_W + PIPE_DX));
}

void Move(Pipe pipes[], const int NUM_PIPES, const float DELTA_TIME)
{
	if (NUM_PIPES > 0)
	{
		for (int i = 0; i < NUM_PIPES; ++i)
		{
			pipes[i].upperBody.x -= PIPE_MS * DELTA_TIME;
			pipes[i].lowerBody.x -= PIPE_MS * DELTA_TIME;
			pipes[i].scoreBody.x -= PIPE_MS * DELTA_TIME;

			if (pipes[i].upperBody.x <= -(PIPE_W + PIPE_W + PIPE_DX))
			{
				ResetPipeX(&pipes[i]);
				SetRandYPos(&pipes[i]);
			}
		}
	}
}

/*
 * TODO: In the future I would like this to be based on the position of the previous pipe
 * so we can avoid pipes spawning too far away from each other and being impossible
 * for the player to reach.
 */
void SetRandYPos(Pipe* p, const int SCREEN_H, const int SCREEN_W)
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
	p->scoreBody.x = GetScreenWidth();
}
