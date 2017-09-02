#include "TooManyBalls.h"
#include <math.h>
#include <stdlib.h>

static void	loop(global *g)
{
	SDL_Event	e;

	while (TRUE) {
		SDL_SetRenderDrawColor(g->rend, 0x20, 0x20, 0x20, 0xFF);
		SDL_RenderClear(g->rend);
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT
					|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				return ;
		draw(g);
		SDL_UpdateWindowSurface(g->win);
	}
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
			grid[i][j] = random() % (NCASE_H - i) + 15;
		}
	}
	grid[i] = NULL;
	return (grid);
}

static int	init(global *g)
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"SDL_Init fail : %s\n", SDL_GetError());
		return (1);
	}
	g->win = SDL_CreateWindow("Too Many Balls", 0, 0,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(!g->win) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Window creation fail : %s\n",SDL_GetError());
		return (1);
	}
	g->surface = SDL_GetWindowSurface(g->win);
	g->rend = SDL_CreateSoftwareRenderer(g->surface);
	if(!g->rend) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Render creation for surface fail : %s\n",SDL_GetError());
		return (1);
	}
	if (TTF_Init() < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"TTF_Init fail : %s\n",TTF_GetError());
		return (1);
	}
	g->nBall	= 0;
	g->score	= 0;
	g->grid = initGrid();
	return (0);
}

int			main(void)
{
	global			g;

	if (init(&g))
		exit(1);
	loop(&g);
	TTF_Quit();
	for (int i = 0; i < NCASE_H; i++) {
		free(g.grid[i]);
	}
	free(g.grid);
	return (0);
}
