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

static void	drawBalls(SDL_Renderer *rend, ball **ball)
{
	SDL_Rect	r;

	r.w = 10;
	r.h = 10;
	r.x = ball[0]->pos.x - 5;
	r.y = ball[0]->pos.y - 5;
	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rend, &r);
}

void	draw(SDL_Renderer *rend, ball **ball)
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
	if (ball[0]->state == 0 && click & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		ball[0]->state = 1;
		ball[0]->dir.x = m.x;
		ball[0]->dir.y = m.y;
	}
	balls(ball);
	drawBalls(rend, ball);
	box.w = WIN_WIDTH / 2;
	box.h = WIN_HEIGHT - 20;
	box.x = WIN_WIDTH / 4;
	box.y = 10;
	SDL_SetRenderDrawColor(rend, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderDrawRect(rend, &box);
}
