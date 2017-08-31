#ifndef TOO_MANY_BALLS
# define TOO_MANY_BALLS

# include <SDL.h>
# include <SDL_ttf.h>
# include "libft.h"

# define WIN_WIDTH	2560
# define WIN_HEIGHT	1440

# define TRUE	1
# define FALSE	0

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

void	draw(SDL_Renderer *rend, ball **ball);
void	balls(ball **ball);

#endif
