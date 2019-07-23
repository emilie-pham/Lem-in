/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/07/23 17:45:08 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

/*
***		NEXT POUR HASH, PREV POUR BFS
*/

typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				visited;
	struct 	s_link	*linked_rooms;
	struct	s_room	*prev;
	struct	s_room	*next;
}					t_room;

typedef struct		s_hash
{
	t_room			*node;
	struct s_hash	*next;
}					t_hash;

/*
***		FLOW MODIFIED BY EDMUND KARP ALGO
*/

typedef struct		s_link
{
	t_room			*dest;
	int				flow;
	struct	s_link	*next;
}					t_link;

typedef struct		s_path
{
	t_room			*room;
	int				ant_index;
	struct	s_path	*next;
}					t_path;

typedef	struct 		s_queue
{
	t_room			*room;
	struct 	s_queue	*next;
}					t_queue;


typedef struct		s_env
{
	char			*line;
	int				ant_nb;
	size_t			table_size;
	t_link			*links;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
	t_hash			*hashtable;
}					t_env;

void	parse(t_env *env);

/*
***		hash
*/

t_hash	*create_hash_table(t_env *env);
t_hash	*fill_hash_table(t_env *env, t_hash *table);

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
