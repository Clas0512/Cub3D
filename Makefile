NAME		= cub3d

LBFT		= libft/libft.a

GNL			= gnl/get_next_line.a

SRCS		= main.c check_map.c check_map_utils.c

COMPILER	= gcc

FLAGS		= -Wall -Wextra -Werror


$(NAME) : $(SRCS)
		$(COMPILER) $(SRCS) $(LBFT) $(GNL) $(FLAGS) -o $(NAME)

all : $(NAME)

$(GNL)	= make -C gnl/

$(LBFT)	= make -C libft/

clean :
		rm -rf $(NAME)

fclean : clean

re : clean all

bonus :
		@echo "nothing"