#include "TooManyBalls.h"
#include <math.h>

void	loop(SDL_Renderer *rend)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            exit (0);
    draw(rend);
}

int		main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surface;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Too Many Balls", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    surface = SDL_GetWindowSurface(win);
    rend = SDL_CreateSoftwareRenderer(surface);
	while (TRUE) {
		SDL_SetRenderDrawColor(rend, 0x20, 0x20, 0x20, 0xFF);
		SDL_RenderClear(rend);
		loop(rend);
    	SDL_UpdateWindowSurface(win);
	}
	return (0);
}
