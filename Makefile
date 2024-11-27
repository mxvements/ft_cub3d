CC=			cc
NAME=		cub3D
CFLAGS=		-Wall -Wextra -Werror -g3
CFLAG_SAN=	-fsanitize=address
MLX_LINUX=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

###############################################################################

SRC_DIR=	./src/
SRC=		main.c 

###############################################################################

LIBFT_DIR=	./libft/
LIBFT=		./libft/libft.a

###############################################################################

GNL_DIR=	./gnl/
GNL_SRCS=	get_next_line.c \
			get_next_line_utils.c

###############################################################################

OBJ_DIR=	./obj/
OBJ=	$(SRC:%.c=$(OBJ_DIR)%.o)

###############################################################################

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

sanitize: fclean $(NAME)
	$(CC) $(CFLAGS) $(CFLAG_SAN) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

norminette:
	norminette $(SRC)

re: fclean all

.PHONY: sanitize clean fclean norminette re