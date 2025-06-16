SRC = main.c \
	utils.c \
	parse.c \
	parse1.c \
	put.c \
	put1.c \
	init.c \
	enermy.c

OBJ = $(SRC:.c=.o)

NAME = so_long

LIBFT = libft/libft.a

MLX_FLAGS = -L. -lmlx -framework OpenGL -framework AppKit

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) libmlx.dylib -o $(NAME) $(MLX_FLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
