# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 11:39:50 by umartin-          #+#    #+#              #
#    Updated: 2022/12/19 17:16:37 by umartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c		\
philo_routine.c		\
utils.c				\
utils2.c			\
utils3.c			\

OBJ = $(SRC:.c=.o)

RM = rm -f
ARRC = ar rc

GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

HEADERS = philo.h
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g3 #-fsanitize=address

all: $(NAME)

m: $(NAME)

$(NAME): $(OBJ)
	@echo "$(WHT)Compiling Philosophers...$(EOC)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Philosophers build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"


re: fclean all

.PHONY: clean re fclean all bonus m rebonus