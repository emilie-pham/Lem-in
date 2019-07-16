/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/07/16 13:31:14 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>


# include <stdio.h>


typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				is_full;
	int				level;
	struct	s_room	*next;
}					t_room;

typedef struct	s_link
{
	t_room			*start;
	t_room			*end;
	char			*start_name;
	char			*end_name;
	struct	s_link	*next;
}				t_link;

typedef struct	s_env
{
	char		*line;
	char		*input;
	int			ant_nb;
	t_link		*links;
	t_room		*rooms;
	t_room		*start;
	t_room		*end;
}				t_env;

/*
***		INITIALIZE
*/

t_env			*initialize_env(t_env **env);

/*
***		PARSER
*/

void			get_input(t_env *env);
int				check_input(t_env *env);

/*
***		CHECK ERRORS
*/

int				check_ants(t_env *env, char **value);
int				get_start_end(t_env *env, char **args, char *startend);


void	parse(t_env *env);

/*
***		rooms
*/

void	parse_rooms(t_env *env);
void	print_list(t_room *head);

/*
***		links
*/

void	add_link(t_env *env, t_link *link);
t_link	*get_link(t_env *env, char *line);
void	print_links(t_link *head);
void	parse_links(t_env *env);

/*
***		checkers
*/

int		is_room(char *line);
int		is_command(char *line);
int		is_comment(char *line);
int		is_link(char *line);

#endif
