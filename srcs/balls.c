#include "TooManyBalls.h"

void		resetBall(ball *b)
{
	b->pos.x = WIN_WIDTH / 2;
	b->pos.y = WIN_HEIGHT - 20;
	b->dir.x = 0.0f;
	b->dir.y = 0.0f;
	b->state = 0;
}

void		balls(ball **ball)
{
	if (ball[0]->state == 0)
		return;

	if (ball[0]->pos.x + ball[0]->dir.x * 5.0f > (float)WIN_WIDTH * 0.75f - 5 ||
		ball[0]->pos.x + ball[0]->dir.x * 5.0f < (float)WIN_WIDTH * 0.25f + 5)
		ball[0]->dir.x *= -1.0f;
	if (ball[0]->pos.y - ball[0]->dir.y * 5.0f < 25.0f)
		ball[0]->dir.y *= -1.0f;
	ball[0]->pos.x += ball[0]->dir.x * 5.0f;
	ball[0]->pos.y -= ball[0]->dir.y * 5.0f;
	if (ball[0]->pos.y > WIN_HEIGHT - 20)
		resetBall(ball[0]);
}
