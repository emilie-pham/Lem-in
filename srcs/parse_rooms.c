/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:25:56 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/30 16:07:35 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*create_room(char *line)
{
	char	**split;
	t_room	*room;

	if (!(split = ft_strsplit(line, ' ')))
		return (NULL);
	if (!(room = ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(split[0]);
	room->coord_x = ft_atoi(split[1]);
	room->coord_y = ft_atoi(split[2]);
	room->visited = 0;
	room->next = NULL;
	room->prev = NULL;
	ft_tabdel(split);
	return (room);
}

void	parse_startend(t_env *env, t_room **table)
{
	t_room	*room;

	room = NULL;
	if (command_type(env->line) == 1)
	{
		get_next_line(0, &env->line);
		if (!is_room(env->line))
			ft_error(4);
		room = create_room(env->line);
		insert_hash_table(table, room);
		env->start = room;
		printf("START %s %d %d\n", env->start->name, env->start->coord_x, env->start->coord_y);
	}
	if (command_type(env->line) == 2)
	{
		get_next_line(0, &env->line);
		if (!is_room(env->line))
			ft_error(4);
		room = create_room(env->line);
		insert_hash_table(table, room);
		env->end = room;
		printf("END   %s %d %d\n", env->end->name, env->end->coord_x, env->end->coord_y);
	}
}
