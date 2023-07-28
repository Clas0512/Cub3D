NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		= check_main.c check_map_utils.c color.c init_data.c \
				get_dir.c init_map.c main.c put_image.c check_and_fill.c \
				check_map_extra.c check_map_utils_3.c init_map_utils.c \
				raycast_utils.c read_map.c check_map.c check_map_utils_2.c

COMPILER	= gcc

FLAGS		= -g -Wall -Wextra -Werror -framework OpenGL -framework AppKit #-fsanitize=address

all : $(ZORT) $(NAME)

$(NAME)	: $(LBFT) $(GNL) $(SRCS)
		$(COMPILER) $(SRCS) $(MLX) $(LBFT) $(GNL) $(FLAGS) -o $(NAME)

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