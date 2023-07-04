NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/gnl.a

SRCS		= main.c check_map.c check_map_utils.c

COMPILER	= gcc

FLAGS		= -Wall -Wextra -Werror -g


$(ZORT)	:
		make -C ./gnl
		make -C ./libft
		
$(NAME)	:
		make -C ./gnl
		make -C ./libft
		$(COMPILER) $(SRCS) $(LBFT) $(GNL) $(FLAGS) -o $(NAME)

all : $(NAME)

clean :
		rm -rf $(NAME)
		make clean -C ./libft

fclean : clean

re : clean all

bonus :
		@echo "nothing"

.PHONY : all clean fclean re bonus