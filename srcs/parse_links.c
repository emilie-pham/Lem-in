/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/29 14:28:06 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_link(t_env *env, t_link *link)
{
	t_link			*current;
	static t_link	*tail;

	current = env->links;
	if (!env->links)
	{
		env->links = link;
		tail = link;
	}
	else
	{
		tail->next = link;
		tail = link;
	}
}

void	linked_rooms(t_room *room, t_room *linked)
{
	t_room *current;

	current = room->linked_rooms->dest;
	if (!current)
	{
		current = linked;
	}
	else
	{
		while (current->next)
			current = current->next;
		current = linked;
	}
}

t_link	*create_link(t_room *start, t_room *end)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link))))
		return (NULL);
	link->dest = end;
	link->from = start;
	linked_rooms(start, end);
	linked_rooms(end, start);
	link->next = NULL;
	return (link);
}

t_room	*find_room(t_env *env, t_room **table, char *room_name)
{
	t_room	*current;
	int		index;

	index = hash_value(room_name);
	current = table[index];
	if (!current->name)
		return (NULL);
	while (current)
	{
		if (!ft_strcmp(current->name, room_name))
			return (current);
		current = current->next;
	}
}

t_link	*get_link(t_env *env, t_room **table, char *line)
{
	char	*start;
	char	*end;
	char	**split;
	t_room	*start_room;
	t_room	*end_room;

	if ((split = (ft_strsplit(line, '-'))))
	{
		start = ft_strdup(split[0]);
		end = ft_strdup(split[1]);
		start_room = find_room(env, table, start);
		end_room = find_room(env, table, end);
		if (start_room && end_room)
			return (create_link(start_room, end_room));
	}
	return (NULL);
}
