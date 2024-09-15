SRCS		= $(wildcard ./*.c) $(wildcard ./gnl/*.c)
OBJS		= $(SRCS:.c=.o)
NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I. -I./gnl

%.o: %.c libft.h ./gnl/get_next_line.h
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

clean:
			@rm -f $(OBJS)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re