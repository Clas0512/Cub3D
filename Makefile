NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

MLX			= mlx/libmlx.a

SRCS		=	*.c

COMPILER	= gcc

FLAGS		= -g -Wall -Wextra -Werror -framework OpenGL -framework AppKit

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