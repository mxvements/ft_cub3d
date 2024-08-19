NAME=cub3D
LIB=minilibx-linux/libmlx_Linux.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Imlx

SRC_PATH=	./src/
SRC_FILES=	game.c

OBJ_DIR = obj/

OBJ=$(SRC_FILES:%.c=$(OBJ_DIR)%.o)
SOFLAGS= -Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm

# rules
all: $(NAME)

Libft/libft.a : 
	@make bonus -C Libft/
	@make -C minilibx-linux/

$(NAME):$(OBJ) Libft/libft.a 
	$(CC) $^ $(LIB) $(SOFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make -C Libft/ clean
	@make -C minilibx-linux/ clean
fclean: clean
	rm -f $(NAME)
	@make -C Libft/ fclean
re: fclean all
	@meke -C Libft/ re
.PHONY: all re fclean clean