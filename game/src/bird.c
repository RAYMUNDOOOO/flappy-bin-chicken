#include "raylib.h"
#include "bird.h"

// DECLARATIONS
void PrepareJump(Bird* bird);
void ApplyVelocities(Bird* bird, const float DELTA_TIME);

// DEFINITIONS
void Init(Bird* bird)
{
	if (bird != NULL)
	{
		bird->body.x = GetScreenWidth() * 0.1;
		bird->body.y = GetScreenHeight() / 2;
		bird->width = 30;
		bird->height = 30;
		bird->jumpStrength = 350;
		bird->yVelocity = 0;
		bird->score = 0;
		bird->gravity = 980;
	}
}

void Tick(Bird* bird, const float DELTA_TIME)
{
	if (IsKeyPressed(KEY_SPACE)) PrepareJump(bird);

	ApplyVelocities(bird, DELTA_TIME);
}

void Draw(Bird* bird)
{
	DrawRectanglePro(bird->body, (Vector2){ player->body.width / 2, player->body.height / 2 }, 0, GOLD);
}


void PrepareJump(Bird* bird)
{
	bird->yVelocity = bird->jumpStrength;
}

void ApplyVelocities(Bird* bird, const float DELTA_TIME)
{
	bird->body.y -= bird->yVelocity * DELTA_TIME;
	bird->yVelocity -= bird->gravity * DELTA_TIME;
}
