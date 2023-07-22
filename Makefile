NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		= main.c check_map.c check_main.c init_data.c init_map.c keyboard.c

COMPILER	= gcc 

FLAGS		= -Wall -Wextra -Werror -framework OpenGL -framework AppKit

all : $(NAME)

$(LBFT):
		make -C ./libft

$(GNL):
		make -C ./gnl

$(MLX):
		make -C ./mlx

$(NAME)	: $(LBFT) $(GNL) $(SRCS)
		$(COMPILER) $(SRCS) $(MLX) $(LBFT) $(GNL) $(FLAGS) -o $(NAME)

clean :
		rm -rf $(NAME)
		make clean -C ./libft
		make clean -C ./gnl
		make clean -C ./mlx

fclean : clean

re : clean all

bonus :
		@echo "nothing"

.PHONY : all clean fclean re bonus