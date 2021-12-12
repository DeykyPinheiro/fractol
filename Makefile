LIBFT_PATH		=	./libraries/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MINILIBX_PATH	=	./libraries/minilibx
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a

SOURCES			= calc_img.c colors.c fractal_set.c ft_atod.c hooks.c
SOURCES			+= math_function.c set_deafault.c zoom.c fractol.c ft_check.c
SOURCES 		+= ft_correct_exit.c

HEADER			= fractol.h

OBJECTS			= 	$(SOURCES:.c=.o)

NAME 			= fractol

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
MLXFLAGS		= -L. -lXext -L. -lX11

AR				= ar
ARFLAGS			= rcs


.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(LIBFT) $(MINILIBX) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)
				$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)


$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

$(MINILIBX):
				$(MAKE) -C $(MINILIBX_PATH)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS)
				$(MAKE) -C $(MINILIBX_PATH) clean

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
				$(RM) fractol
				$(RM) a.out
				$(RM) *.a

re:				fclean all

erro:
	./$(NAME) j -0.7885 -0.785

norm:
				norminette $(SOURCES)

r:				all
				./$(NAME) j -0.8 0.156

b:	all
	./$(NAME) b

m:	all
	./$(NAME) m

.PHONY:	all clean fclean re run norm
