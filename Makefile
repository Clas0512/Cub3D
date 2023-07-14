NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		= main.c check_map.c check_main.c

COMPILER	= gcc

FLAGS		= -Wall -Wextra -Werror -framework OpenGL -framework AppKit -g

$(ZORT)	:
		make -C ./gnl
		make -C ./libft
		make -C ./mlx
		
$(NAME)	: $(LIBFT) $(GNL) $(SRCS)
		$(COMPILER) $(SRCS) $(MLX) $(LBFT) $(GNL) $(FLAGS) -o $(NAME)

$(GNL) :
		make -C ./gnl

$(LBFT) :
		make -C ./libft

all : $(NAME)

clean :
		rm -rf $(NAME)
		make clean -C ./libft

fclean : clean

re : clean all

bonus :
		@echo "nothing"

.PHONY : all clean fclean re bonus