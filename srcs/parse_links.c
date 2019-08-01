/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/08/01 14:25:55 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_link(t_room *room, t_link *link)
{
	t_link	*tail;

	if (!room->linked_rooms)
	{
		room->linked_rooms = link;
		return ;
	}
	tail = room->linked_rooms;
	while (tail->next)
		tail = tail->next;
	tail->next = link;
}

void	create_links(t_room **start, t_room **end)
{
	t_link	*firstlink;
	t_link	*secondlink;
	t_link	*tail;

	if (!(firstlink = ft_memalloc(sizeof(t_link))))
		return ;
	if (!(secondlink = ft_memalloc(sizeof(t_link))))
		return ;
	firstlink->dest = *end;
	secondlink->dest = *start;
	firstlink->flow = 0;
	secondlink->flow = 0;
	firstlink->rev = secondlink;
	secondlink->rev = firstlink;
	firstlink->next = NULL;
	secondlink->next = NULL;
	add_link(*start, firstlink);
	add_link(*end, secondlink);
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
	return (NULL);
}

int		get_link(t_env *env, t_room **table, char *line)
{
	char	*start;
	char	*end;
	char	**split;
	t_room	*start_room;
	t_room	*end_room;

	if ((split = (ft_strsplit(line, '-'))))
	{
		env->flag_link = 1;
		start = ft_strdup(split[0]);
		end = ft_strdup(split[1]);
		start_room = find_room(env, table, start);
		end_room = find_room(env, table, end);
		if (start_room && end_room)
		{
			create_links(&start_room, &end_room);
			ft_tabdel(split);
			free(start);
			free(end);
		}
		else
		{
			if (start_room)
				free(start);
			if (end_room)
				free(end);
			return (-1);
		}
	}
	return (-1);
}
