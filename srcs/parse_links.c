/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/30 15:05:08 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_link(t_room *room, t_link *link)
{
	t_link	*tail;

	tail = room->linked_rooms;
	while (tail)
		tail = tail->next;
	tail = link;
}

void	create_links(t_room *start, t_room *end)
{
	t_link	*firstlink;
	t_link	*secondlink;

	if (!(firstlink = ft_memalloc(sizeof(t_link))))
		return ;
	if (!(secondlink = ft_memalloc(sizeof(t_link))))
		return ;
	firstlink->dest = end;
	secondlink->dest = start;
	firstlink->flow = 0;
	secondlink->flow = 0;
	firstlink->rev = secondlink;
	secondlink->rev = firstlink;
	firstlink->next = NULL;
	secondlink->next = NULL;
	add_link(start, firstlink);
	add_link(end, secondlink);
	// printf("FIRSTLINK : from %s to %s\n", start->name, firstlink->dest->name);
	// printf("SECONDLINK : from %s to %s\n\n", end->name, secondlink->dest->name);
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

int		get_link(t_env *env, t_room **table, char *line)
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
		{
			create_links(start_room, end_room);
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
