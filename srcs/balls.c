#include "TooManyBalls.h"
#include <math.h>

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

float		clamp(float val, float low, float high)
{
	return(ft_max(low, ft_min(high, val)));
}

static void	drawCircle(vec2 p, float rad, global *g)
{
	vec2	dir;
	vec2	tmp;

	dir.x = 1.0;
	dir.y = 0.0;
	SDL_SetRenderDrawColor(g->rend, 0x00, 0xFF, 0x00, 0xFF);
	for(float a = -1800.0f; a < 1800.0f; a++) {
		tmp.x = dir.x * cos(a * M_PI / 1800.0f) - dir.y * sin(a * M_PI / 1800.0f);
		tmp.y = dir.x * sin(a * M_PI / 1800.0f) + dir.y * cos(a * M_PI / 1800.0f);
		dir.x = tmp.x;
		dir.y = tmp.y;
		SDL_RenderDrawPoint(g->rend, p.x + (dir.x * rad), p.y + (dir.y * rad));
	}
}

static int	checkTile(ball *b, global *g)
{
	vec2	block;
	vec2	diff;
	vec2	nearest;
	int		ball_line;
	int		ball_col;

	ball_col = ((int)b->pos.x - MARGIN) / CASE_WIDTH;
	ball_line = ((int)b->pos.y - 10) / CASE_HEIGHT;

	for (int i = ball_line - 50; i < ball_line + 50; i++) {
		for (int j = ball_col - 50; j < ball_col + 50; j++) {
			if (i >= 0 && i < NCASE_H && j >= 0 && j < NCASE_W/* && g->grid[i][j] > 0*/)
			{
				block.x = (j * CASE_WIDTH) + (CASE_WIDTH / 2);
				block.y = (i * CASE_HEIGHT) + (CASE_HEIGHT / 2);
				drawCircle(b->pos, 100.0f, g);
				diff.x = b->pos.x - MARGIN - block.x;
				diff.y = b->pos.y - 10 - block.y;
				nearest.x = clamp(diff.x, -(CASE_WIDTH / 2), CASE_WIDTH / 2);
				nearest.y = clamp(diff.y, -(CASE_HEIGHT / 2), CASE_HEIGHT / 2);
				diff.x = block.x + nearest.x;
				diff.y = block.y + nearest.y;
				float x = fabs(b->pos.x - MARGIN - diff.x);
				float y = fabs(b->pos.y - 10 - diff.y);
				if (sqrt((x * x) + (y * y)) <= 100.0f) {
					g->grid[i][j] = 0;
				//	return (1);
				}
			}
		}
	}
	return (0);

/*	if ((ball_col >= 0 && ball_col < NCASE_H) &&
 *			(ball_line >= 0 && ball_line < NCASE_W) &&
 *			(*(ball_case = &(g->grid[ball_col][ball_line])) != 0))
\*		(*ball_case)--;*/
}

void		balls(ball *b, global *g)
{
	for (int i = 0; i < g->nBall; i++) {
		if (i != 0 && b[i].state == 0) {
			if (distBall(b[i - 1]) > 50) {
				b[i].state = 1;
				g->nLaunchedBalls++;
			}
			continue;
		}
		if (b[i].pos.x + b[i].dir.x * SPEED > (WIN_WIDTH + BOX_WIDTH) / 2 - 5 ||
			b[i].pos.x + b[i].dir.x * SPEED < (WIN_WIDTH - BOX_WIDTH) / 2 + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * SPEED < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * SPEED;
		b[i].pos.y -= b[i].dir.y * SPEED;
		if (b[i].pos.y > BOX_HEIGHT || checkTile(&(b[i]), g)) {
			resetBall(&(b[i]));
			g->nLaunchedBalls--;
		}
	}
}
