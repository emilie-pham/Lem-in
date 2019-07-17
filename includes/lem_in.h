/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/07/17 13:15:43 by yoribeir         ###   ########.fr       */
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
	int				capacity;
	struct	s_link	*next;
}				t_link;

typedef struct	s_env
{
	char		*line;
	int			ant_nb;
	t_link		*links;
	t_room		*rooms;
	t_room		*start;
	t_room		*end;
}				t_env;


void	parse(t_env *env);

/*
***		rooms
*/

t_room	*create_room(char *line);
void	add_room(t_env *env, t_room *room);
void	parse_startend(t_env *env);

/*
***		links
*/

void	add_link(t_env *env, t_link *link);
t_link	*get_link(t_env *env, char *line);

void	parse_links(t_env *env);

/*
***		checkers
*/

int		is_room(char *line);
int		is_command(char *line);
int		is_comment(char *line);
int		is_link(char *line);
int		command_type(char *line);

/*
***		utils
*/

void	ft_error(int error);
void	print_links(t_link *head);
void	print_rooms(t_room *head);
#endif
