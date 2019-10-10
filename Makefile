# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/17 15:48:36 by yoribeir          #+#    #+#              #
#    Updated: 2019/08/05 14:57:12 by yoribeir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=lem-in
INCLUDES	= includes
LIBS		= libft
LIB			= ft
FLAGS		= -Wall -Werror -Wextra -g
DFLAGS		= -g3 -fsanitize=address,undefined
SRCS		= lem_in.c opti.c check_rooms.c check_links.c check_commands.c \
edmond.c hash.c init.c parse_links.c parse_rooms.c parser.c paths.c solutions.c \
print_sol.c print_map.c utils.c bfs.c queue.c
SRCSREP		= srcs
OBJS		= $(SRCS:.c=.o)

BLANK		=\x1b[0m
GREEN		=\x1b[32;01m
RED			=\x1b[31;01m
YELLOW		=\x1b[38;5;228m

all: $(NAME)

%.o: $(SRCSREP)/%.c
	@gcc $(FLAGS) -I$(INCLUDES) -c $^

debug: 
	@gcc $(DFLAGS) srcs/*.c libft/*.c -o $(NAME) 

$(NAME): $(OBJS)
	@echo "\n$(RED)CREATING LEM IN ...$(BLANK)"
	@make -C libft
	@gcc $(FLAGS) -I$(INCLUDES) $^ -L$(LIBS) -l$(LIB) -o $@
	@echo "$(GREEN)[lem-in created]$(BLANK)"

clean:
	@echo "\n$(RED)CLEANING OBJECTS FILES ...$(BLANK)"
	@rm -f $(OBJS)
	@make clean -C libft
	@echo "$(YELLOW)[object files removed]$(BLANK)"
fclean: clean
	@echo "\n$(RED)REMOVING LEM IN ...$(BLANK)"
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(YELLOW)[lem-in removed]$(BLANK)"

re: fclean all