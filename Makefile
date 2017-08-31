# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/18 01:13:53 by gudemare          #+#    #+#              #
#    Updated: 2017/08/31 03:04:53 by aviau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	TooManyBalls

#==============================================================================#
#                            Compilation parameters                            #
#==============================================================================#

CC				=	clang
CFLAGS			=	-Wall -Wextra `sdl2-config --cflags` -O2 #-L/Users/gudemare/.brew/lib -I/Users/gudemare/.brew/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
LIBS			=	libft
LIBFT_DIR		=	libft

FFLAGS			=	-F . `sdl2-config --libs` -lSDL2_ttf

SDL2_HEADERS	=	~/.brew/include/SDL2
HEADERS_LIB		=	libft/includes/
HEADERS_DIR		=	includes/
HFLAGS			=	-I $(HEADERS_DIR) -I $(HEADERS_LIB) -I $(SDL2_HEADERS)
LFLAGS			=	-lft -L$(LIBFT_DIR)
SRCS_DIR		=	srcs/
SRCS_LIST		=	\
					main.c\
					balls.c\
					draw.c
SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR		=	./objs/
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

#==============================================================================#
#                             Colors Escape Codes                              #
#==============================================================================#

END_GRAPHICS	=	\e[0m
BOLD			=	\e[1m
DARK			=	\e[2m
ITALIC			=	\e[3m
UNDERSCORE		=	\e[4m
REVERSE_VID		=	\e[7m
BLACK			=	\e[30m
RED				=	\e[31m
GREEN			=	\e[32m
YELLOW			=	\e[33m
BLUE			=	\e[34m
MAGENTA			=	\e[35m
CYAN			=	\e[36m
WHITE			=	\e[37m
BLACK_BG		=	\e[40m
RED_BG			=	\e[41m
GREEN_BG		=	\e[42m
YELLOW_BG		=	\e[43m
BLUE_BG			=	\e[44m
MAGENTA_BG		=	\e[45m
CYAN_BG			=	\e[46m
WHITE_BG		=	\e[47m

#==============================================================================#
#                                 Instructions                                 #
#==============================================================================#

.PHONY : all clean fclean re debug debug_lib debug_re project_re $(LIBS) $(SUBPROJECTS)

all: $(NAME)

$(NAME) : $(LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(HFLAGS) $(LFLAGS) $(FFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(GREEN) has successfully compiled.$(END_GRAPHICS)\n"
@printf "$(MAGENTA)Warning : -Werror is disabled\n$(END_GRAPHICS)"

$(LIBS) :
	@printf "\e[K$(CYAN)Compiling $(BOLD)libft$(END_GRAPHICS)$(CYAN) ...\n\e[A$(END_GRAPHICS)"
	@make -C $(LIBFT_DIR) -j8
	@printf "$(GREEN)Library $(BOLD)libft$(END_GRAPHICS)$(GREEN) successfully compiled.$(END_GRAPHICS)\n"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@printf "\e[K$(CYAN)Compiling $(BOLD)$(notdir $<)$(END_GRAPHICS)$(CYAN) ...\n\e[A$(END_GRAPHICS)"
	@$(CC) $(CFLAGS) $(HFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean 1>/dev/null
	@printf "$(BOLD)$(YELLOW)$(NAME)$(END_GRAPHICS)$(YELLOW)'s objects files have been removed.$(END_GRAPHICS)\n"
fclean :
	@rm -rf $(NAME) $(OBJS_DIR)
	@make -C $(LIBFT_DIR) fclean 1>/dev/null
	@printf "$(YELLOW)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(YELLOW) and its projects files have been removed.$(END_GRAPHICS)\n"

re: fclean all

project_re:
	@rm -rf $(OBJS_DIR) $(NAME)
	@make

debug_lib :
	@make -C $(LIBFT_DIR) -j8 debug

debug : CFLAGS=-Wall -Wextra -fsanitize=address -g
debug : debug_lib all
	@printf "\e[K$(GREEN)The program $(BOLD)$(NAME)$(END_GRAPHICS)$(GREEN) has successfully compiled $(YELLOW)(with debug symbols).$(END_GRAPHICS)\n"

debug_re : fclean debug
