#include "TooManyBalls.h"
#include <math.h>

void			resetBall(ball *b)
{
	b->pos.x = WIN_WIDTH / 2;
	b->pos.y = BOX_HEIGHT;
	b->dir.x = 0.0f;
	b->dir.y = 0.0f;
	b->state = 3;
}

float			distBall(ball b)
{
	float xd = (WIN_WIDTH / 2) - b.pos.x;
	float yd = BOX_HEIGHT - b.pos.y;
	return (sqrt(xd * xd + yd * yd));
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

static float	dot(vec2 dirA, vec2 dirB)
{
	return((dirA.x * dirB.x) + (dirA.y * dirB.y));
}

static int		lrud(vec2 dir)
{
	vec2 compass[4] = {(vec2){0.0f, 1.0f},(vec2){1.0f, 0.0f},(vec2){0.0f, -1.0f},(vec2){-1.0f, 0.0f}};
	float max = 0.0f;
	unsigned int bestMatch = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dotProduct = dot(dir, compass[i]);
		if (dotProduct > max) {
			max = dotProduct;
			bestMatch = i;
		}
	}
	return bestMatch;
}

static void	checkTile(ball *b, global *g)
{
	vec2	block;
	vec2	diff;
	vec2	nearest;
	int		ball_line;
	int		ball_col;

	ball_col = ((int)b->pos.x - MARGIN) / CASE_WIDTH;
	ball_line = ((int)b->pos.y - 10) / CASE_HEIGHT;

	for (int i = ball_line - 10; i < ball_line + 10; i++) {
		for (int j = ball_col - 10; j < ball_col + 10; j++) {
			if (i >= 0 && i < NCASE_H && j >= 0 && j < NCASE_W && g->grid[i][j] > 0)
			{
				block.x = (j * CASE_WIDTH) + (CASE_WIDTH / 2.0f);
				block.y = (i * CASE_HEIGHT) + (CASE_HEIGHT / 2.0f);
				drawCircle(b->pos, 10.0f, g);
				diff.x = b->pos.x - MARGIN - block.x;
				diff.y = b->pos.y - 10 - block.y;
				nearest.x = ft_max(-(CASE_WIDTH / 2.0f), ft_min(CASE_WIDTH / 2.0f, diff.x));
				nearest.y = ft_max(-(CASE_HEIGHT / 2.0f), ft_min(CASE_HEIGHT / 2.0f, diff.y));
				diff.x = block.x + nearest.x;
				diff.y = block.y + nearest.y;
				float x = fabs(b->pos.x - MARGIN - diff.x);
				float y = fabs(b->pos.y - 10 - diff.y);
				if (sqrt((x * x) + (y * y)) <= 10.0f) {
					g->grid[i][j]--;
					float	penetration;
					int		dir = lrud(b->dir);
					ft_putstr(ft_itoa(dir));
					if (dir == 1 || dir == 3) {
						ft_putendl("LR");
						penetration = 10.0f - fabs(diff.x);
						b->pos.x = -(b->pos.x);
						if (dir == 3)
							b->pos.x += penetration;
						else
							b->pos.x -= penetration;
					}
					else {
						ft_putendl("UD");
						penetration = 10.0f - fabs(diff.y);
						b->pos.y = -(b->pos.y);
						if (dir == 0)
							b->pos.y -= penetration;
						else
							b->pos.y += penetration;
					}
				}
			}
		}
	}
}

void		balls(ball *b, global *g)
{
	for (unsigned int i = 0; i < g->nBall; i++) {
		if (i != 0 && b[i].state == 0) {
			if (distBall(b[i - 1]) > 50) {
				b[i].state = 1;
				g->nLaunchedBalls++;
			}
			break;
		}
		if (b[i].pos.x + b[i].dir.x * SPEED > (WIN_WIDTH + BOX_WIDTH) / 2 - 5 ||
			b[i].pos.x + b[i].dir.x * SPEED < (WIN_WIDTH - BOX_WIDTH) / 2 + 5)
			b[i].dir.x *= -1.0f;
		if (b[i].pos.y - b[i].dir.y * SPEED < 25.0f)
			b[i].dir.y *= -1.0f;
		b[i].pos.x += b[i].dir.x * SPEED;
		b[i].pos.y -= b[i].dir.y * SPEED;
		checkTile(&(b[i]), g);
		if (b[i].pos.y > BOX_HEIGHT) {
			resetBall(&(b[i]));
			g->nLaunchedBalls--;
		}
	}
}
