#ifndef TOO_MANY_BALLS
# define TOO_MANY_BALLS

# include <SDL.h>
# include <SDL_ttf.h>
# include "libft.h"

# define WIN_WIDTH		2560
# define WIN_HEIGHT		1440
# define RECT_WIDTH		800
# define RECT_HEIGHT	(WIN_HEIGHT-20)

# define	TRUE	1
# define	FALSE	0

# define	NBALL 60
# define	NCASE_W 20
# define	NCASE_H 25

typedef struct	vec2
{
	float		x;
	float		y;
}				vec2;

typedef struct	ball
{
	vec2		pos;
	vec2		dir;
	short		state;
}				ball;

void	draw(SDL_Renderer *rend, int **grid, ball *b);
void	balls(ball *ball);

#endif
