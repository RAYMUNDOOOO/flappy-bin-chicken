#include "raylib.h"

typedef struct Bird
{
	Rectangle body;
	int jumpStrength;
	float yVelocity;
	int score;
	int gravity;
	float rotation;
	float rotationRate;
} Bird;

void InitBird(Bird* bird);
void TickBird(Bird* bird, const float DELTA_TIME);
void DrawBird(Bird* bird);
