NAME	= gnl.a
SRCS	= get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
		@ar rc $(NAME) $(OBJS)

fclean :
	@rm -rf *.o
	@rm -rf $(NAME)

.PHONY : all fclean