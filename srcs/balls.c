#include "TooManyBalls.h"

#define SPEED 50.0f

void			resetBall(ball *b)
{
	b->pos.x = WIN_WIDTH / 2;
	b->pos.y = BOX_HEIGHT;
	b->dir.x = 0.0f;
	b->dir.y = 0.0f;
	b->state = 0;
}

float			distBall(ball b)
{
	float xd = (WIN_WIDTH / 2) - b.pos.x;
	float yd = BOX_HEIGHT - b.pos.y;

	return (sqrt(xd * xd + yd * yd));
}

void			balls(ball *b, global g)
{
	for (int i = 0; i < g.nBall; i++) {
		if (i != 0 && b[i].state == 0) {
			if (distBall(b[i - 1]) > 50)
				b[i].state = 1;
			continue;
		}
		if (b[i].pos.x + b[i].dir.x * SPEED > (WIN_WIDTH + BOX_WIDTH) / 2 - 5 ||
			b[i].pos.x + b[i].dir.x * SPEED < (WIN_WIDTH - BOX_WIDTH) / 2 + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * SPEED < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * SPEED;
		b[i].pos.y -= b[i].dir.y * SPEED;
		if (b[i].pos.y > BOX_HEIGHT)
			resetBall(&(b[i]));
	}
}
