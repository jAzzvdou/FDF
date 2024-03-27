NAME	=	fdf

SRCS	=	main.c          \
		verify_map.c    \
		map.c           \
		get_next_line.c \
		draw.c          \
		utils.c         \
		utils2.c

SRCS_BONUS	=

OBJS	=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

CC	=	cc

CFLAGS	=	-g -Wall -Werror -Wextra

RM	=	rm -rf

MLX	=	minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(SRCS) $(MLX) -o $(NAME) -Imlx_linux -lXext -lX11 -lm

.c.o:
		$(CC) $(CFLAGS) -c $<

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS_BONUS)
		$(CC) -o $(NAME) $(OBJS_BONUS)

.PHONY: all clean fclean re bonus
