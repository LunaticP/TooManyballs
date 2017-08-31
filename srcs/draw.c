#include "TooManyBalls.h"

static void	draw_rect(SDL_Renderer *rend, int **grid)
{
	SDL_Rect	rect;

	rect.w = (RECT_WIDTH - 10) / NCASE_W - 10;
	rect.h = (RECT_HEIGHT / 2 - 10) / NCASE_H - 5;
	for (int col = 0; col < NCASE_H; col++) {
		rect.y = (col * (rect.h + 10)) + NCASE_W;
		for(int block = 0; block < NCASE_W; block++) {
			if (grid[col][block]) {
				SDL_SetRenderDrawColor(rend,
						(Uint8)(255 - grid[col][block] * 10),
						(Uint8)(grid[col][block] * 10),
						(Uint8)(255 - grid[col][block] * 10), 0xFF);
				rect.x = (block * (rect.w + 10)) + (WIN_WIDTH - RECT_WIDTH) / 2 + 10;
				SDL_RenderFillRect(rend, &rect);
			}
		}
	}
}

static void	draw_ray(SDL_Renderer *rend,vec2 m)
{
	int		x;
	int		y;

	SDL_SetRenderDrawColor(rend, 0x00, 0xFF, 0x00, 0xFF);
	x = (WIN_WIDTH / 2) + m.x * 350.0f;
	y = (WIN_HEIGHT - 20) - m.y * 350.0f;
	SDL_RenderDrawLine(rend, WIN_WIDTH / 2, WIN_HEIGHT - 20, x, y);
}

static void	drawBalls(SDL_Renderer *rend, ball *b)
{
	SDL_Rect	r;

	r.w = 10;
	r.h = 10;
	for (int i = 0; i < NBALL; i++) {
		r.x = b[i].pos.x - 5;
		r.y = b[i].pos.y - 5;
		SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(rend, &r);
	}
}

static void	startBalls(ball *b, vec2 m)
{
	for (int i = 0; i < NBALL; i++)
		if (b[i].state == 1)
			return;
	for (int i = 0; i < NBALL; i++) {
		b[i].dir.x = m.x;
		b[i].dir.y = m.y;
	}
	b[0].state = 1;
}

void	draw(SDL_Renderer *rend, int **grid, ball *b)
{
	SDL_Rect	box;
	vec2		m;
	int			x;
	int			click;
	float		l;

	click = SDL_GetMouseState(&x, NULL);
	m.x = (float)x / ((float)WIN_WIDTH / 2.0f) - 1.0f;
	m.y = cos(m.x * (M_PI_2 - 0.08f));
	l = sqrt((m.x * m.x) + (m.y * m.y));
	m.x /= l;
	m.y /= l;
	draw_rect(rend, grid);
	draw_ray(rend, m);
	if (click & SDL_BUTTON(SDL_BUTTON_LEFT))
		startBalls(b, m);
	balls(b);
	drawBalls(rend, b);
	box.w = RECT_WIDTH;
	box.h = RECT_HEIGHT;
	box.x = (WIN_WIDTH - RECT_WIDTH) / 2;
	box.y = 10;
	SDL_SetRenderDrawColor(rend, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderDrawRect(rend, &box);
}
