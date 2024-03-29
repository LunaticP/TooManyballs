#include "TooManyBalls.h"

static void	draw_score(global *g, SDL_Rect rect, int score)
{
	SDL_Color	couleur = {0x00,0x00,0xFF,0xFF};
	SDL_Surface	*text;
	SDL_Rect	dst;
	char		*force;

	force = ft_itoa(score);
	text = TTF_RenderText_Blended(g->case_font, force, couleur);
	dst.x = rect.x + CASE_WIDTH / 2 - text->w / 2;
	dst.y = rect.y + CASE_HEIGHT / 2 - text->h / 2;
	SDL_BlitSurface(text, NULL, g->surface, &dst);
	SDL_FreeSurface(text);
	ft_strdel(&force);
}

static void	draw_rect(global *g)
{
	SDL_Rect	rect;
	SDL_Surface *image[3];
	SDL_Texture *tex[3];

	image[0] = IMG_Load("textures/sample.png");
	if(!image[0]) {
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(1);
	}
	tex[0] = SDL_CreateTextureFromSurface(g->rend, image[0]);
	image[1] = IMG_Load("textures/brick2_b.jpg");
	if(!image[1]) {
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(1);
	}
	tex[1] = SDL_CreateTextureFromSurface(g->rend, image[1]);
	image[2] = IMG_Load("textures/you-dont-say-meme-th.jpg");
	if(!image[2]) {
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(1);
	}
	tex[2] = SDL_CreateTextureFromSurface(g->rend, image[2]);
	rect.w = CASE_WIDTH;
	rect.h = CASE_HEIGHT;
	for (int col = 0; col < NCASE_H; col++) {
		rect.y = (col * CASE_HEIGHT) + 10;
		for(int block = 0; block < NCASE_W; block++) {
			if (g->grid[col][block] > 0) {
				rect.x = (block * CASE_WIDTH) + (WIN_WIDTH - BOX_WIDTH) / 2;
				SDL_RenderCopy(g->rend, tex[rect.y % 3], NULL, &rect);
				draw_score(g, rect, g->grid[col][block]);
			}
		}
	}
	SDL_FreeSurface(image[0]);
	SDL_FreeSurface(image[1]);
	SDL_FreeSurface(image[2]);
}

static void	draw_ray(SDL_Renderer *rend, vec2 m)
{
	int		x;
	int		y;

	SDL_SetRenderDrawColor(rend, 0x00, 0xFF, 0x00, 0xFF);
	x = (WIN_WIDTH / 2) + m.x * 350.0f;
	y = BOX_HEIGHT - m.y * 350.0f;
	SDL_RenderDrawLine(rend, WIN_WIDTH / 2, BOX_HEIGHT, x, y);
}

static void	drawBalls(SDL_Renderer *rend, ball *b, global g)
{
	SDL_Rect	r;

	r.w = 10;
	r.h = 10;
	for (unsigned int i = 0; i < g.nBall; i++) {
		r.x = b[i].pos.x - 5;
		r.y = b[i].pos.y - 5;
		SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(rend, &r);
	}
}

static void	startBalls(vec2 m, global *g)
{
	for (unsigned int i = 0; i <= g->nBall; i++) {
		if ((g->b)[i].state == e_ACTIVE)
			return;
		if ((g->b)[i].state == e_NULL)
			break;
	}
	free(g->b);
	ft_assert(g->b = (ball*)malloc(sizeof(ball) * (g->nBall + 1)));
	for (unsigned int i = 0; i < g->nBall; i++) {
		(g->b)[i].pos.x = WIN_WIDTH / 2;
		(g->b)[i].pos.y = BOX_HEIGHT;
		(g->b)[i].dir.x = m.x;
		(g->b)[i].dir.y = m.y;
		(g->b)[i].state = e_INACTIVE;
	}
	(g->b)[0].state = e_ACTIVE;
	(g->b)[g->nBall].state = e_NULL;
	g->inTurn = 1;
	g->nLaunchedBalls = 1;
}

void	draw(global *g)
{
	SDL_Rect	box;
	vec2		m;
	int			x;
	int			click;
	float		l;

	click = SDL_GetMouseState(&x, NULL);
	m.x = (float)x / ((float)WIN_WIDTH / 2.0f) - 1.0f;
	m.y = cos(m.x * (M_PI_2 - 0.08f));
	l = sqrt((m.x * m.x) + (m.y * m.y));
	m.x /= l;
	m.y /= l;
	draw_rect(g);
	draw_ray(g->rend, m);
	if (g->nLaunchedBalls > 0) {
		balls(g->b, g);
		drawBalls(g->rend, g->b, *g);
	}
	if (g->nLaunchedBalls == 0 || (click & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
		nextTurn(g);
		if (click & SDL_BUTTON(SDL_BUTTON_LEFT))
			startBalls(m, g);
	}
	box.w = BOX_WIDTH;
	box.h = BOX_HEIGHT;
	box.x = (WIN_WIDTH - BOX_WIDTH) / 2;
	box.y = 10;
	SDL_SetRenderDrawColor(g->rend, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderDrawRect(g->rend, &box);
}
