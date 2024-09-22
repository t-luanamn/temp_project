NAME			= mrt
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g #-fsanitize=address

SRCS			= $(shell find ./srcs -name '*.c')
SRCS_INC		= ./incs
OBJS			= $(SRCS:.c=.o)

# LIB
LIBFT			= ./libft
LIBFT_L			= -L $(LIBFT) -lft
ifeq ($(shell uname), Linux)
	LIBMLX		= ./minilibx_linux
	LIBMLX_L	= -L $(LIBMLX) -lmlx -lXext -lX11 -lm -lz
else
	LIBMLX		= ./minilibx_opengl
	LIBMLX_L	= -L $(LIBMLX) -lmlx -framework OpenGL -framework AppKit
endif

%.o: %.c
	$(CC) -I $(SRCS_INC) -I $(LIBFT) -I $(LIBMLX) $(CFLAGS) -c $< -o $@

# Colour
RST				= "\033[0m"
R				= "\033[0;31m"
G				= "\033[0;32m"
C				= "\033[0;36m"

.SILENT:

all:			$(NAME)

$(NAME):		$(OBJS)
				echo $(C)"Making Libft..."$(RST)
				make -C $(LIBFT)
				echo $(C)"Libft compiled"$(RST)
				echo $(C)"Making mlx..."$(RST)
				make -C $(LIBMLX)
				echo $(C)"mlx compiled"$(RST)
				echo $(C)"Making $(NAME)..."$(RST)
				gcc $(OBJS) $(CFLAGS) $(LIBFT_L) $(LIBMLX_L) -o $(NAME)
				echo $(C)"$(NAME) compiled"$(RST)
				echo $(G)"\nLauch: ./$(NAME) *.rt\n"$(RST)

clean:
				echo $(R)"Cleaning..."$(RST)
				make -C $(LIBFT) clean
				rm -f $(OBJS)
				echo $(R)"Cleaned"$(RST)

fclean:			clean
				make -C $(LIBFT) fclean
				make -C $(LIBMLX) clean
				rm -rf $(NAME)
				echo $(R)"Removed everything"$(RST)

re:				fclean all

.PHONY:			all clean fclean re