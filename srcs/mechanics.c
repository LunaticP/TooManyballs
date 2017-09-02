#include "TooManyBalls.h"

void	nextTurn(global *g)
{
	if (!(g->inTurn))
		return ;
	g->nBall *= 1.5f;
	g->nBall++;
	g->turn++;
	g->inTurn = 0;
}
