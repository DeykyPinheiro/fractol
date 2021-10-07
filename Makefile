LIBFT_PATH		=	./libraries/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MINILIBX_PATH	=	./libraries/minilibx
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a

SOURCES			= calc_img.c colors.c fractal_set.c ft_atod.c hooks.c
SOURCES			+= math_function.c set_deafault.c zoom.c fractol.c

HEADER			= fractol.h

OBJECTS			= 	$(SOURCES:.c=.o)

NAME 			= fractol.a

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
MLXFLAGS		= -L. -lXext -L. -lX11

AR				= ar
ARFLAGS			= rc


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
				$(MAKE) -C $(MINILIBX_PATH) clean
				$(RM) $(OBJECTS)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
				$(RM) a.out
				$(RM) *.a

re:				fclean all

r:
				clang -Wall -Werror -Wextra *.c -O3 ./libraries/libft/libft.a ./libraries/minilibx/libmlx.a -L. -lXext -L. -lX11 && ./a.out j -0.8 0.156


.PHONY:			all clean fclean re run
