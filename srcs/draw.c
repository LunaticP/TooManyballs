#include "TooManyBalls.h"

static void	draw_rect(SDL_Renderer *rend)
{
	SDL_Rect	rect;

	rect.w = ((WIN_WIDTH / 2) - 10) / 20 - 10;
	rect.h = ((WIN_HEIGHT - 20) / 2 - 10) / 25 - 5;
	for (int col = 0; col < 25; col++) {
		rect.y = (col * (rect.h + 10)) + 20;
		for(int block = 0; block < 20; block++) {
		SDL_SetRenderDrawColor(rend, 255 - col * 10, col * 10, 255 - col * 10, 0xFF);
		rect.x = (block * (rect.w + 10)) + WIN_WIDTH / 4 + 10;
		SDL_RenderFillRect(rend, &rect);
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

static void	drawBalls(SDL_Renderer *rend, ball *b, global g)
{
	SDL_Rect	r;

	r.w = 10;
	r.h = 10;
	for (int i = 0; i < g.nBall; i++) {
		r.x = b[i].pos.x - 5;
		r.y = b[i].pos.y - 5;
		SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(rend, &r);
	}
}

static void	startBalls(ball **b, vec2 m, global *g)
{
	for (int i = 0; i < g->nBall; i++)
		if ((*b)[i].state == 1)
			return;
	g->nBall++;
	ft_assert(*b = (ball*)malloc(sizeof(ball) * g->nBall));
	for (int i = 0; i < g->nBall; i++) {
 		(*b)[i].pos.x = WIN_WIDTH / 2;
		(*b)[i].pos.y = WIN_HEIGHT - 20;
		(*b)[i].dir.x = m.x;
		(*b)[i].dir.y = m.y;
		(*b)[i].state = 0;
	}
	(*b)[0].state = 1;
}

void	draw(SDL_Renderer *rend, ball **b, global *g)
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
	draw_ray(rend, m);
	draw_rect(rend);
	if (click & SDL_BUTTON(SDL_BUTTON_LEFT))
		startBalls(b, m, g);
	balls(*b, *g);
	drawBalls(rend, *b, *g);
	box.w = WIN_WIDTH / 2;
	box.h = WIN_HEIGHT - 20;
	box.x = WIN_WIDTH / 4;
	box.y = 10;
	SDL_SetRenderDrawColor(rend, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderDrawRect(rend, &box);
}
