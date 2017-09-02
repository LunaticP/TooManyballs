#ifndef TOO_MANY_BALLS
# define TOO_MANY_BALLS

# include <SDL.h>
# include <SDL_ttf.h>
# include "libft.h"

# define WIN_WIDTH		2560
# define WIN_HEIGHT		1440
# define BOX_WIDTH		(WIN_WIDTH / 2)
# define BOX_HEIGHT		(WIN_HEIGHT - 20)
# define NCASE_W		20
# define NCASE_H		40
# define CASE_WIDTH		(BOX_WIDTH  / NCASE_W)
# define CASE_HEIGHT	(BOX_HEIGHT / NCASE_H)
# define MARGIN			((WIN_WIDTH - BOX_WIDTH) / 2)

# define SPEED			8.0f

# define TRUE			1
# define FALSE			0


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

typedef struct	global
{
	SDL_Surface		*surface;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	TTF_Font		*font;
	ball			*b;
	int 			nBall;
	int				score;
	int				**grid;
}					global;

void			draw(global *g);
void			balls(ball *ball, global *g);

#endif
