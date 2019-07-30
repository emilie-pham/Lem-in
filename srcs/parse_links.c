/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:25:56 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/30 16:08:57 by anonymous        ###   ########.fr       */
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
	free(tail);
}

t_link	*create_link(t_room *start, t_room *end)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link))))
		return (NULL);
	link->dest = end;
	link->from = start;
	link->next = NULL;
	return (link);
}

void	*create_links(t_room *start, t_room *end)
{
	t_link	*firstlink;
	t_link	*secondlink;

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
	return (firstlink); // return non NULL sinon le parsing s'arrete
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
		free(start);
		free(end);
		ft_tabdel(split);
		if (start_room && end_room)
			return (create_links(start_room, end_room));
		else
			ft_error(2);
	}
	return (NULL);
}
