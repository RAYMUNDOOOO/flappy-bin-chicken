#include "raylib.h"
#include "bird.h"
#include "stddef.h"

const int MAX_ROT = -20;
const int MIN_ROT = 65;
bool inputEnabled = true;
Sound flapSfx;

// DECLARATIONS
void PrepareJump(Bird* bird);
void ApplyVelocities(Bird* bird, const float DELTA_TIME);
void ApplyRotation(Bird* bird, const float DELTA_TIME);

// DEFINITIONS
void InitBird(Bird* bird)
{
	if (bird != NULL)
	{
		bird->body.x = GetScreenWidth() * 0.1;
		bird->body.y = GetScreenHeight() / 2;
		bird->body.width = 30;
		bird->body.height = 30;
		bird->jumpStrength = 550;
		bird->yVelocity = 0;
		bird->score = 0;
		bird->gravity = 980 * 2;
		bird->rotation = 0;
		bird->rotationRate = 100;
	}

    if (IsAudioDeviceReady()) flapSfx = LoadSound("../res/audio/flap.wav");
}

void TickBird(Bird* bird, const float DELTA_TIME)
{
    if (inputEnabled)
    {
        if (IsKeyPressed(KEY_SPACE)) 
        {
            PrepareJump(bird);
            PlaySound(flapSfx);
        }
    }

	ApplyVelocities(bird, DELTA_TIME);
	ApplyRotation(bird, DELTA_TIME);
}

void DrawBird(Bird* bird)
{
	DrawRectanglePro(bird->body, (Vector2){ bird->body.width / 2, bird->body.height / 2 }, bird->rotation, GOLD);
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

void ApplyRotation(Bird* bird, const float DELTA_TIME)
{
	if (bird->yVelocity > 0)
	{
		bird->rotation -= bird->rotationRate * DELTA_TIME * 7;
		if (bird->rotation <= MAX_ROT) bird->rotation = MAX_ROT;
	}

	if (bird->yVelocity < 0)
	{
		bird->rotation += bird->rotationRate * DELTA_TIME;
		if (bird->rotation >= MIN_ROT) bird->rotation = MIN_ROT;
	}
}

void EnableInput()
{
    inputEnabled = true;
}

void DisableInput()
{
    inputEnabled = false;
}
