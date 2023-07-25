NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		= main.c check_map.c check_map_extra.c check_main.c color.c check_map_utils.c check_map_utils_2.c check_and_fill.c read_map.c init_data.c put_image.c init_map_utils.c init_map.c raycast_utils.c

COMPILER	= gcc

FLAGS		= -g -Wall -Wextra -Werror -framework OpenGL -framework AppKit

all : $(ZORT) $(NAME)

$(NAME)	: $(LBFT) $(GNL) $(SRCS)
		$(COMPILER) $(SRCS) $(MLX) $(LBFT) $(GNL) $(FLAGS) -g -o $(NAME)

$(LBFT):
		make -C libft

$(GNL):
		make -C gnl
		

clean :
		rm -rf $(NAME)
		make clean -C ./libft

fclean : clean

re : clean all

bonus :
		@echo "nothing"

.PHONY : all clean fclean re bonus