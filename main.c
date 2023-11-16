#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define GRAVITY 980 // To effect how the bird flies.

// Screen attributes.
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 900

// Pipe attributes.
#define PIPE_DELTA_X 180
#define PIPE_DELTA_Y 150
#define PIPE_WIDTH 80
#define PIPE_MS 120

bool exitWindow = false;

typedef struct Pipe
{
	// The positions from which the pipe will be rendered and their size (l x h).
	Vector2 upperPosition; 
	Vector2 lowerPosition;
	Rectangle upperBody;
	Rectangle lowerBody;
	Rectangle scoreBody;
} Pipe;

int GetNumPipes(const int screenWidth, const int pipeWidth, const int pipeDeltaX);
void InitPipes(Pipe pipes[], const int numPipes);
void MovePipes(Pipe pipes[], const int numPipes, const float deltaTime);
void DrawPipes(Pipe pipes[], const int numPipes);
void SetRandYPos(Pipe* pipe);

// Bird attributes.
typedef struct Bird
{
	// The position from which the bird will be rendered and its size (l x h).
	Vector2 position;
	Rectangle body;

	/*
	 * The JUMP_STRENGTH will be used to set the vertical velocity of the bird
	 * and each tick, GRAVITY will reduce the yVelocity to simulate it
	 * dropping in the air.
	 */
	int jumpStrength;
	float yVelocity;
	int score;
} Bird;

Bird* InitBird();
void Jump(Bird* bird);
void ApplyGravity(Bird* bird, float deltaTime);
void CheckCollisions(Bird* bird, Pipe pipes[], const int numPipes);

int main(void)
{
	// Initialise the window.
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bin Chicken");
	SetTargetFPS(240);
	
	// Initialise entities in the game (bird and pipes).
	Bird* player = InitBird();

	const int numPipes = GetNumPipes(GetScreenWidth(), PIPE_WIDTH, PIPE_DELTA_X) + 2;
	Pipe pipes[numPipes];
	InitPipes(pipes, numPipes);
	
	// Tick.
	while (!exitWindow)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			Jump(player);
		}

		// Applying movement to bird and pipes.
		ApplyGravity(player, GetFrameTime());
		MovePipes(pipes, numPipes, GetFrameTime());
		CheckCollisions(player, pipes, numPipes);
		char scoreStr[20];
		sprintf(scoreStr, "%d", player->score);

		// Drawing.
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectanglePro(player->body, (Vector2){ player->body.width / 2, player->body.height / 2 }, 0, GOLD);
		DrawText(scoreStr, GetScreenWidth() / 2, GetScreenHeight() * 0.1, 12, RAYWHITE);
		DrawPipes(pipes, numPipes);
		EndDrawing();
	}

	free(player);
	player = NULL;

	CloseWindow();
	return 0;
}

Bird* InitBird()
{
	Bird* bird = (Bird*)malloc(sizeof(Bird));
	if (bird != NULL)
	{
		bird->position.x = GetScreenWidth() * 0.1;
		bird->position.y = GetScreenHeight() / 2;
		bird->body.x = bird->position.x;
		bird->body.y = bird->position.y;
		bird->body.width = 30;
		bird->body.height = 30;
		bird->jumpStrength = 350;
		bird->yVelocity = 0;
		bird->score = 0;
	}

	return bird;
}

void Jump(Bird* bird)
{
	if (bird != NULL) bird->yVelocity = bird->jumpStrength;
}

void ApplyGravity(Bird* bird, float deltaTime)
{
	if (bird != NULL)
	{
		bird->position.y -= bird->yVelocity * deltaTime;
		bird->body.y = bird->position.y;
		bird->yVelocity -= GRAVITY * deltaTime;
	}
}

void CheckCollisions(Bird* bird, Pipe pipes[], const int numPipes)
{
	for (int i = 0; i < numPipes; ++i)
	{
		if (CheckCollisionRecs(bird->body, pipes[i].upperBody))
		{
			printf("Collision detected! \n");
			exitWindow = true;
		}
			
		if (CheckCollisionRecs(bird->body, pipes[i].lowerBody))
		{
			printf("Collision detected! \n");
			exitWindow = true;
		}

		if (CheckCollisionRecs(bird->body, pipes[i].scoreBody)) bird->score++;
	}
}

int GetNumPipes(const int screenWidth, const int pipeWidth, const int pipeDeltaX)
{
	return (screenWidth / (pipeWidth + pipeDeltaX));
}

// Initialise the drawing position of the pipes based on the screen width, height and the gaps between them.
void InitPipes(Pipe pipes[], const int numPipes)
{
	if (sizeof(*pipes) > 0)
	{
		const int middleOfScreen = GetScreenHeight() / 2; // We will determine the drawing positions of the pipes from this.
		for (int i = 0; i < numPipes; ++i)
		{
			pipes[i].upperPosition.x = GetScreenWidth() + (i * (PIPE_WIDTH + PIPE_DELTA_X));
			pipes[i].lowerPosition.x = GetScreenWidth() + (i * (PIPE_WIDTH + PIPE_DELTA_X));
			pipes[i].upperBody.x = pipes[i].upperPosition.x;
			pipes[i].lowerBody.x = pipes[i].lowerPosition.x;
			pipes[i].upperBody.width = PIPE_WIDTH;
			pipes[i].upperBody.height = GetScreenHeight();
			pipes[i].lowerBody.width = PIPE_WIDTH;
			pipes[i].lowerBody.height = GetScreenHeight();
			pipes[i].scoreBody.x = pipes[i].upperPosition.x - 300;
			pipes[i].scoreBody.width = PIPE_WIDTH;
			pipes[i].scoreBody.height = PIPE_DELTA_Y + 50;

			pipes[i].upperBody.y = (GetScreenHeight() / 2 - 100) - GetScreenHeight();
			pipes[i].lowerBody.y = (GetScreenHeight() / 2) + 100;
			pipes[i].scoreBody.y = pipes[i].upperBody.y + GetScreenHeight();
		}
	}
}

void MovePipes(Pipe pipes[], const int numPipes, const float deltaTime)
{
	if (sizeof(*pipes) > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			pipes[i].upperPosition.x -= PIPE_MS * deltaTime;
			pipes[i].upperBody.x = pipes[i].upperPosition.x;
			pipes[i].lowerPosition.x -= PIPE_MS * deltaTime;
			pipes[i].lowerBody.x = pipes[i].lowerPosition.x;
			// pipes[i].scoreBody.x -= pipes[i].lowerPosition.x;

			if (pipes[i].upperPosition.x <= -PIPE_WIDTH)
			{
				pipes[i].upperPosition.x = GetScreenWidth();
				pipes[i].upperBody.x = pipes[i].upperPosition.x;
				pipes[i].lowerPosition.x = GetScreenWidth();
				pipes[i].lowerBody.x = pipes[i].lowerPosition.x;
				// pipes[i].scoreBody.x = pipes[i].lowerPosition.x;

				SetRandYPos(&pipes[i]);
			}
		}
	}
}

void DrawPipes(Pipe pipes[], const int numPipes)
{
	if (sizeof(*pipes) > 0)
	{
		for (int i = 0; i < numPipes; ++i)
		{
			DrawRectanglePro(pipes[i].upperBody, (Vector2){ 0, 0 }, 0, RED);
			DrawRectanglePro(pipes[i].lowerBody, (Vector2){ 0, 0 }, 0, RAYWHITE);
			DrawRectanglePro(pipes[i].scoreBody, (Vector2){ 0, 0 }, 0, YELLOW);
		}
	}
}

void SetRandYPos(Pipe* pipe)
{
	const int maxPosY = (GetScreenHeight() / 2) + (GetScreenHeight() * 0.3);
	const int minPosY = (GetScreenHeight() / 2) - (GetScreenHeight() * 0.3);

	int randY =  minPosY + (rand() % (maxPosY - minPosY));
	pipe->upperPosition.y = randY - GetScreenHeight();
	pipe->lowerPosition.y = randY + PIPE_DELTA_Y;
	pipe->upperBody.y = pipe->upperPosition.y;
	pipe->lowerBody.y = pipe->lowerPosition.y;
	// pipe->scoreBody.y = pipe->upperPosition.y + GetScreenHeight();
}
