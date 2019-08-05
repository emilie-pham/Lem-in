/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/08/05 15:17:28 by yoribeir         ###   ########.fr       */
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

void	*create_links(t_room *start, t_room *end)
{
	t_link	*firstlink;
	t_link	*secondlink;
	t_link	*tail;

	if (!(firstlink = ft_memalloc(sizeof(t_link))))
		return (NULL);
	if (!(secondlink = ft_memalloc(sizeof(t_link))))
		return (NULL);
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
	return (firstlink);
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

void	*get_link(t_env *env, t_room **table, char *line)
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
		ft_tabdel(split);
		if (start_room)
			free(start);
		if (end_room)
			free(end);
		if (start_room && end_room)
			return (create_links(start_room, end_room));
		else
			ft_error(2);
	}
	return (NULL);
}
