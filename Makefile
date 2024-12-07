
# LIB=minilibx-linux/libmlx_Linux.a
# CC=gcc
# CFLAGS=-Wall -Wextra -Werror -Imlx

# SOFLAGS= -Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm

# # rules
# all: $(NAME)

# Libft/libft.a : 
# 	@make bonus -C Libft/
# 	@make -C minilibx-linux/

# $(NAME):$(OBJ) Libft/libft.a 
# 	$(CC) $^ $(LIB) $(SOFLAGS) -o $(NAME)

# $(OBJ_DIR)%.o: $(SRC_PATH)%.c
# 	@mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf $(OBJ)
# 	rm -rf $(OBJ_DIR)
# 	@make -C Libft/ clean
# 	@make -C minilibx-linux/ clean
# fclean: clean
# 	rm -f $(NAME)
# 	@make -C Libft/ fclean
# re: fclean all
# 	@meke -C Libft/ re
# .PHONY: all re fclean clean

# compilation variables

CC=			cc
NAME=		cub3D
CFLAGS=		-Wall -Wextra -Werror -g3
CFLAG_SAN=	-fsanitize=address
MLX_LINUX=	-Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

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
SRC=		main.c\
			game.c
			

GAME_DIR=	./src/game/
GAME=		ray_casting.c\
			mov.c\
			printMap.c\
			adicional.c

PRS_DIR=	./src/parse_input/
PSR=		parse_input.c \
			check_input.c

ERR_DIR=	./src/errors/
ERR=		print_error.c 


# libft

LIBFT_DIR=	./libft/
LIBFT=		./libft/libft.a

# gnl

GNL_DIR=	./gnl/
GNL_SRCS=	get_next_line.c \
			get_next_line_utils.c

MLX_DIR=	./minilibx-linux
MLX=		./minilibx-linux/libmlx_Linux.a

###############################################################################

# objs

OBJ_DIR=	./obj/
OBJ=	$(GNL_SRCS:%.c=$(OBJ_DIR)%.o) \
		$(SRC:%.c=$(OBJ_DIR)%.o) \
		$(GAME:%.c=$(OBJ_DIR)%.o) \
		$(PSR:%.c=$(OBJ_DIR)%.o) \
		$(ERR:%.c=$(OBJ_DIR)%.o)

###############################################################################

# rules

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling libft...$(RESET_COLOR)"
	make -C $(LIBFT_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Compiling mlx_linux...$(RESET_COLOR)"
	make -C $(MLX_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)[$(NAME)]	Linking objs files with libraries...$(RESET_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_LINUX) -o $(NAME)

$(OBJ_DIR)%.o: $(GNL_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(GAME_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)%.o: $(PRS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(ERR_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BOLD)$(DARK_BLUE)[$(NAME)]	Commpiling $<...$(RESET_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

sanitize: fclean $(NAME)
	$(CC) $(CFLAGS) $(CFLAG_SAN) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)

clean:
	@echo "$(ORANGE)[$(NAME)]	Cleaning libft...$(RESET_COLOR)"
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	@echo "$(PINK)[$(NAME)]	Removing $(OBJ_DIR)...$(RESET_COLOR)"
	rm -rf $(OBJ)

fclean: clean
	@echo "$(BOLD)$(ORANGE)[$(NAME)]	fCleaning libft...$(RESET_COLOR)"
	make fclean -C $(LIBFT_DIR)
	@echo "$(ORANGE)[$(NAME)]	Cleaning mlx_linux..$(RESET_COLOR)"
	make clean -C $(MLX_DIR)
	@echo "$(BOLD)$(PINK)[$(NAME)]	Removing $(NAME)...$(RESET_COLOR)"
	rm -rf $(NAME)

norminette:
	@echo "$(BOLD)$(PINK)[$(NAME)]	Running norminette on all source files...$(RESET_COLOR)"
	norminette $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c

re: fclean all

.PHONY: sanitize clean fclean norminette re
