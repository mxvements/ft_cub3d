NAME=cub3D
LIB=minilibx/libmlx_Linux.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Imlx

FILES = src/game.c

OBJ=$(%.c=%.o)
SOFLAGS=-Iinclude -ldl -lglfw -pthread -lm

# rules
all: $(NAME)

Libft/libft.a : 
	@make bonus -C Libft/
	@make -C minilibx/

$(NAME):Libft/libft.a $(OBJ)
	$(CC) $^ $(LIB) $(SOFLAGS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJ)
	@make -C Libft/ clean
	@make -C minilibx/ clean
fclean: clean
	rm -f $(NAME)
	@make -C Libft/ fclean
re: fclean all
	@meke -C Libft/ re
.PHONY: all re fclean clean