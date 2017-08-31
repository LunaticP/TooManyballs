#include "TooManyBalls.h"
#include <math.h>
#include <stdlib.h>

SDL_Window		*win;
SDL_Renderer	*rend;

static void	loop(ball **ball)
{
    SDL_Event	e;

	SDL_SetRenderDrawColor(rend, 0x20, 0x20, 0x20, 0xFF);
	SDL_RenderClear(rend);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            exit (0);
    draw(rend, ball);
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
	ball			*b;

	if (init(surface))
		exit(1);
	b = (ball*)malloc(sizeof(ball));
 	b[0].pos.x = WIN_WIDTH / 2;
	b[0].pos.y = WIN_HEIGHT - 20;
	b[0].state = 0;
	while (TRUE)
		loop(&b);
	return (0);
}
