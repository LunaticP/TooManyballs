#ifndef TOO_MANY_BALLS
# define TOO_MANY_BALLS

# include <SDL.h>
# include <SDL_ttf.h>
# include <time.h>
# include "libft.h"

# define WIN_WIDTH		2560
# define WIN_HEIGHT		1440
# define BOX_WIDTH		(WIN_WIDTH / 2)
# define BOX_HEIGHT		(WIN_HEIGHT - 20)
# define NCASE_W		2
# define NCASE_H		12
# define CASE_WIDTH		(BOX_WIDTH  / NCASE_W)
# define CASE_HEIGHT	(BOX_HEIGHT / NCASE_H)
# define MARGIN			((WIN_WIDTH - BOX_WIDTH) / 2)

# define SPEED			5.0f


# define TRUE			1
# define FALSE			0

enum			e_ball_states
{
	e_INACTIVE,
	e_ACTIVE,
	e_TERMINATED,
	e_NULL
};

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
	TTF_Font		*score_font;
	TTF_Font		*case_font;
	ball			*b;
	unsigned int	**grid;
	unsigned int 	nBall;
	unsigned int	nLaunchedBalls;
	unsigned int	turn;
	unsigned int	inTurn;
	unsigned int	score;
}					global;

void			nextTurn(global *g);
void			resetBall(ball *b);
void			draw(global *g);
void			balls(ball *ball, global *g);

#endif
