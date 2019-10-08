# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/17 15:48:36 by yoribeir          #+#    #+#              #
#    Updated: 2019/08/16 16:10:49 by yoribeir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =lem-in
INCLUDES = includes
LIBS = libft
LIB = ft
# FLAGS = -Wall -Werror -Wextra
SRCS = lem_in.c bfs.c checkers.c edmond.c hash.c init.c parse_links.c \
parse_rooms.c parser.c paths.c print_sol.c print_map.c solutions.c utils.c
SRCSREP = srcs
OBJS = $(SRCS:.c=.o)

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