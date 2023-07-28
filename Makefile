NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		=	check_main.c check_map_utils.c color.c get_dir.c init_map.c \
				read_map.c calc_move.c check_map.c check_map_utils_2.c \
				init_map_utils.c main.c put_image.c check_and_fill.c \
				check_map_extra.c check_map_utils_3.c init_data.c keyboard.c \
				raycast_utils.c

CC			= gcc

FLAGS		= -Wall -Wextra -Werror -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME)	: $(LBFT) $(GNL) $(MLX) $(SRCS)
		@$(CC) $(SRCS) $(MLX) $(LBFT) $(FLAGS) $(GNL) -o $(NAME)

$(LBFT):
		@make -C libft

$(GNL):
		@make -C gnl
	
$(MLX):
		@make -C mlx

clean :
		@rm -rf $(NAME)
		@make fclean -C libft
		@make fclean -C gnl
		@make clean -C mlx

fclean : clean

re : clean all

bonus :
		@echo "nothing"

.PHONY : all clean fclean re bonus