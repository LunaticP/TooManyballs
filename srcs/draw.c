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

static void	draw_ray(SDL_Renderer *rend)
{
	int		x;
	int		y;
	float	vx;
	float	vy;
	float	l;

	SDL_GetMouseState(&x, &y);
	SDL_SetRenderDrawColor(rend, 0x00, 0xFF, 0x00, 0xFF);
	vx = (float)x / ((float)WIN_WIDTH / 2.0f) - 1.0f;
	vy = cos(vx * (M_PI_2 - 0.08f));
	l = sqrt((vx * vx) + (vy * vy));
	vx /= l;
	vy /= l;
	x = (WIN_WIDTH / 2) + vx * 350.0f;
	y = (WIN_HEIGHT - 20) - vy * 350.0f;
	SDL_RenderDrawLine(rend, WIN_WIDTH / 2, WIN_HEIGHT - 20, x, y);
}

void	draw(SDL_Renderer *rend)
{
	SDL_Rect	box;

	draw_ray(rend);
	draw_rect(rend);
	box.w = WIN_WIDTH / 2;
	box.h = WIN_HEIGHT - 20;
	box.x = WIN_WIDTH / 4;
	box.y = 10;
	SDL_RenderDrawRect(rend, &box);
}
