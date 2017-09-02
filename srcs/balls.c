#include "TooManyBalls.h"

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

void		checkTile(ball b, global *g)
{
	int		ball_col;
	int		ball_line;
	int		*ball_case;

	ball_col = (int)b.pos.y % NCASE_H;
	ball_line = (int)b.pos.x % NCASE_W;
	if ((ball_col >= 0 && ball_col < NCASE_H) &&
			(ball_line >= 0 && ball_line < NCASE_W) &&
			(*(ball_case = &(g->grid[ball_col][ball_line])) != 0))
		(*ball_case)--;
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
		if (b[i].pos.x + b[i].dir.x * SPEED > (WIN_WIDTH + BOX_WIDTH) / 2 - 5 ||
			b[i].pos.x + b[i].dir.x * SPEED < (WIN_WIDTH - BOX_WIDTH) / 2 + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * SPEED < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * SPEED;
		b[i].pos.y -= b[i].dir.y * SPEED;
		checkTile(b[i], g);
		if (b[i].pos.y > BOX_HEIGHT)
			resetBall(&(b[i]));
	}
}
