#include "TooManyBalls.h"

static void	moveGridDown(global *g)
{
	int				i;
	unsigned int	*tmp;

	tmp = g->grid[NCASE_H - 1];
	for (i = 0; i < NCASE_W; i++)
		if (tmp[i] != 0) {
			ft_putendl("You lost !");
			exit(EXIT_SUCCESS);
		}
	for (i = NCASE_H - 1; i > 0; i--)
		g->grid[i] = g->grid[i - 1];
	g->grid[0] = tmp;
	for (i = 0; i < NCASE_W; i++) {
		g->grid[0][i] = 0;
		g->grid[1][i] = ((random() % (3)) == 0) ? (g->turn) : 0;
	}
}

void		nextTurn(global *g)
{
	if (!(g->inTurn))
		return ;
	g->nBall++;
	g->turn++;
	g->inTurn = 0;
	moveGridDown(g);
}
