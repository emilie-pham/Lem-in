/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/19 14:19:42 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_link(t_env *env, t_link *link)
{
	t_link	*current;

	current = env->links;
	if (!env->links)
		env->links = link;
	else
	{
		while (current->next)
			current = current->next;
		current->next = link;
	}
}

t_link	*create_link(t_room *start, t_room *end)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link))))
		return (NULL);
	link->r1 = start;
	link->r2 = end;
	link->next = NULL;
	return (link);
}

t_room	*find_room(t_env *env, char *room_name)
{
	t_room	*current;

	current = env->rooms;
	while (current)
	{
		if (!ft_strcmp(current->name, room_name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

//	version avec split, a voir si c'est pas trop lourd

t_link	*get_link(t_env *env, char *line)
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
		start_room = find_room(env, start);
		end_room = find_room(env, end);
		if (start_room && end_room)
			return (create_link(start_room, end_room));
	}
	return (NULL);
}

// t_link	*get_link(t_env *env, char *line)
// {
// 	char	*start;
// 	char	*end;
// 	char	*dash;
// 	t_room	*start_room;
// 	t_room	*end_room;

// 	if ((dash = (ft_strchr(line, '-'))))
// 	{
// 		start = ft_strsub(line, 0, dash - line);
// 		end = ft_strsub(dash + 1, 0, ft_strlen(line));
// 		start_room = find_room(env, start);
// 		end_room = find_room(env, end);
// 		if (start_room && end_room)
// 			return (create_link(start_room, end_room));
// 	}
// 	return (NULL);
// }
