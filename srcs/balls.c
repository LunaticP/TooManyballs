#include "TooManyBalls.h"

#define SPEED 4.0f

void		resetBall(ball *b)
{
	b->pos.x = WIN_WIDTH / 2;
	b->pos.y = WIN_HEIGHT - 20;
	b->dir.x = 0.0f;
	b->dir.y = 0.0f;
	b->state = 0;
}

float		sq(float n)
{
	return (n * n);
}

float		distBall(ball b)
{
	float xd = (WIN_WIDTH / 2) - b.pos.x;
	float yd = (WIN_HEIGHT - 20) - b.pos.y;

	return (sqrt(xd * xd + yd * yd));
}

void		checkTile(ball b, global *g)
{
	g->grid[g->nBall]
		[(int)b.pos.x % NCASE_W] = 0;
//		[(int)((b.pos.x - (WIN_WIDTH + RECT_WIDTH) / 2) / (RECT_WIDTH - 10) / NCASE_W - 10)] = 0;
}

void		balls(ball *b, global *g)
{
	for (int i = 0; i < g->nBall; i++) {
		if (i != 0 && b[i].state == 0) {
			if (distBall(b[i - 1]) > 50)
				b[i].state = 1;
			continue;
		}
		if (b[i].pos.x + b[i].dir.x * SPEED > (WIN_WIDTH + RECT_WIDTH) / 2 - 5 ||
			b[i].pos.x + b[i].dir.x * SPEED < (WIN_WIDTH - RECT_WIDTH) / 2 + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * SPEED < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * SPEED;
		b[i].pos.y -= b[i].dir.y * SPEED;
		checkTile(b[i], g);
		if (b[i].pos.y > WIN_HEIGHT - 20)
			resetBall(&(b[i]));
	}
}
