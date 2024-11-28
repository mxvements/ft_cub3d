# compilation variables

CC=			cc
NAME=		cub3D
CFLAGS=		-Wall -Wextra -Werror -g3
CFLAG_SAN=	-fsanitize=address
MLX_LINUX=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# colors

LIGHT_BLUE = \033[38;2;53;200;240m
DARK_BLUE = \033[0;34m
ORANGE = \033[38;5;214m
PINK = \033[38;5;213m
BOLD = \033[1m
RESET_COLOR = \033[0m

###############################################################################

# src

SRC_DIR=	./src/
SRC=		main.c 

# libft

LIBFT_DIR=	./libft/
LIBFT=		./libft/libft.a

# gnl

GNL_DIR=	./gnl/
GNL_SRCS=	get_next_line.c \
			get_next_line_utils.c

###############################################################################

# objs

OBJ_DIR=	./obj/
OBJ=	$(SRC:%.c=$(OBJ_DIR)%.o)

###############################################################################

# rules

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling libft...$(RESET_COLOR)"
	make -C $(LIBFT_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling mlx_linux...$(RESET_COLOR)"
	make -C mlx_linux
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Linking objs files with libraries...$(RESET_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

sanitize: fclean $(NAME)
	$(CC) $(CFLAGS) $(CFLAG_SAN) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

clean:
	@echo "$(ORANGE)[$(NAME)]	Cleaning libft...$(RESET_COLOR)"
	make clean -C $(LIBFT_DIR)
	make clean -C mlx_linux
	@echo "$(PINK)[$(NAME)]	Removing $(OBJ_DIR)...$(RESET_COLOR)"
	rm -rf $(OBJ)

fclean: clean
	@echo "$(BOLD)$(ORANGE)[$(NAME)]	fCleaning libft...$(RESET_COLOR)"
	make fclean -C $(LIBFT_DIR)
	@echo "$(ORANGE)[$(NAME)]	Cleaning mlx_linux..$(RESET_COLOR)"
	make clean -C mlx_linux
	@echo "$(BOLD)$(PINK)[$(NAME)]	Removing $(NAME)...$(RESET_COLOR)"
	rm -rf $(NAME)

norminette:
	@echo "$(BOLD)$(PINK)[$(NAME)]	Running norminette on all source files...$(RESET_COLOR)"
	norminette $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c

re: fclean all

.PHONY: sanitize clean fclean norminette re