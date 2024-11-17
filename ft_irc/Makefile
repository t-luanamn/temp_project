NAME	= ircserv

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow


SRC		= $(wildcard ./src/*.cpp) main.cpp

OBJ		= $(SRC:.cpp=.o)

HEADER	= $(wildcard ./inc/*.hpp)

.SILENT:

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER)
			@echo "\033[36mMaking $(NAME)...\033[0m"
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)
			@echo "\033[36m$(NAME) compiled\033[0m"
			@echo "\033[32mExecution: ./$(NAME)\033[0m"

%.o: %.cpp
			$(CC) $(FLAGS) -c $< -o $@

clean:		
			rm -f $(OBJ)
			@echo "\033[31mCleaned\033[0m"

fclean:		clean
			rm -f $(NAME)
			@echo "\033[31mCleaned everything\033[0m"

re:			fclean all

.PHONY: all clean fclean re
