#include "TooManyBalls.h"
#include <math.h>
#include <stdlib.h>

SDL_Window		*win;
SDL_Renderer	*rend;
ball			*b;

static void	loop(global *g)
{
    SDL_Event	e;

	SDL_SetRenderDrawColor(rend, 0x20, 0x20, 0x20, 0xFF);
	SDL_RenderClear(rend);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT
				|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            exit (0);
    draw(rend, &b, g);
    SDL_UpdateWindowSurface(win);
}

static int	init(SDL_Surface *surface)
{
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"SDL_Init fail : %s\n", SDL_GetError());
        return (1);
	}
    win = SDL_CreateWindow("Too Many Balls", 0, 0,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(!win) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Window creation fail : %s\n",SDL_GetError());
        return (1);
    }
    surface = SDL_GetWindowSurface(win);
    rend = SDL_CreateSoftwareRenderer(surface);
    if(!rend) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Render creation for surface fail : %s\n",SDL_GetError());
        return (1);
    }
	return (0);
}

static int	**initGrid()
{
	int		i;
	int		j;
	int		**grid;

	ft_assert(grid = (int **)malloc(sizeof(int **) * (NCASE_H + 1)));
	for (i = 0; i < NCASE_H; i++) {
		ft_assert(grid[i] = (int *)malloc(sizeof(int *) * NCASE_W));
		for (j = 0; j < NCASE_W; j++) {
			grid[i][j] = i + 1;
		}
	}
	grid[i] = NULL;
	return (grid);
}

int			main(void)
{
	SDL_Surface		*surface = NULL;
	global			g;

	if (init(surface))
		exit(1);
	g.nBall	= 0;
	g.score	= 0;
	g.grid = initGrid();
	while (TRUE)
		loop(&g);
	for (int i = 0; i < NCASE_H; i++) {
		free(g.grid[i]);
	}
	free(g.grid);
	free(b);
	return (0);
}
