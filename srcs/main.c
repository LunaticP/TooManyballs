#include "TooManyBalls.h"
#include <math.h>

SDL_Window		*win;
SDL_Renderer	*rend;

static void	loop(void)
{
    SDL_Event e;

	SDL_SetRenderDrawColor(rend, 0x20, 0x20, 0x20, 0xFF);
	SDL_RenderClear(rend);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            exit (0);
    draw(rend);
    SDL_UpdateWindowSurface(win);
}

static int	init(SDL_Surface *surface)
{
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return (1);
	}
    win = SDL_CreateWindow("Too Many Balls", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(!win) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return (1);
    }
    surface = SDL_GetWindowSurface(win);
    rend = SDL_CreateSoftwareRenderer(surface);
    if(!rend) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return (1);
    }
	return (0);
}

int			main(void)
{
	SDL_Surface		*surface = NULL;

	if (init(surface))
		exit(1);
	while (TRUE)
		loop();
	return (0);
}
