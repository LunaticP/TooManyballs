#include "TooManyBalls.h"

void		resetBall(ball *b)
{
	b->pos.x = WIN_WIDTH / 2;
	b->pos.y = WIN_HEIGHT - 20;
	b->dir.x = 0.0f;
	b->dir.y = 0.0f;
	b->state = 0;
}

void		balls(ball *b)
{
	for (int i = 0; i < NBALL; i++) {
		if (i != 0 && b[i].state == 0) {
			if (b[i - 1].pos.y < WIN_HEIGHT - 50)
				b[i].state = 1;
			continue;
		}
		if (b[i].pos.x + b[i].dir.x * 5.0f > (float)WIN_WIDTH * 0.75f - 5 ||
			b[i].pos.x + b[i].dir.x * 5.0f < (float)WIN_WIDTH * 0.25f + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * 5.0f < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * 5.0f;
		b[i].pos.y -= b[i].dir.y * 5.0f;
		if (b[i].pos.y > WIN_HEIGHT)
			resetBall(&(b[i]));
	}
}
