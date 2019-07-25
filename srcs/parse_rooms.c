/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:19:34 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/23 17:54:24 by yoribeir         ###   ########.fr       */
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
	room->next = NULL;
	return (room);
}

void	add_room(t_env *env, t_room *room)
{
	t_room	*current;

	current = env->rooms;
	if (!env->rooms)
		env->rooms = room;
	else
	{
		while (current->next)
			current = current->next;
		current->next = room;
	}
}

void	parse_startend(t_env *env)
{
	t_room	*room;

	room = NULL;
	if (command_type(env->line) == 1)
	{
		get_next_line(0, &env->line);
		add_room(env, room = create_room(env->line));
		env->start = room;
		// printf("start	%s %d %d\n", env->start->name, env->start->coord_x, env->start->coord_y);
	}
	if (command_type(env->line) == 2)
	{
		get_next_line(0, &env->line);
		add_room(env, room = create_room(env->line));
		env->end = room;
		// printf("end	%s %d %d\n", env->end->name, env->end->coord_x, env->end->coord_y);
	}
}
