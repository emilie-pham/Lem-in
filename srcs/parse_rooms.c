/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:19:34 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/16 15:38:38 by yoribeir         ###   ########.fr       */
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

int		is_room_name(char *line)
{
	if (line && ft_strlen(line))
	{
		if (line[0] == 'L' || line[0] == '#')
			return (0);
	}
	return (1);
}

int		is_room(char *line)
{
	char	**split;
	int		count;
	int		ret;

	count = 0;
	ret = 0;
	if (!(split = ft_strsplit(line, ' ')))
		return (ret);
	while (split[count])
		count++;
	if (count == 3)
	{
		if (is_room_name(split[0]) && ft_strdigit(split[1]) &&
			ft_strdigit(split[2]))
			ret = 1;
	}
	return (ret);
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

void	print_list(t_room *head)
{
	t_room *current;

	current = head;
	while (current)
	{
		printf("room	%s %d %d\n", current->name, current->coord_x, current->coord_y);
		current = current->next;
	}
}

void	parse_rooms(t_env *env)
{
	env->rooms = NULL;
	env->links = NULL;
	while (get_next_line(0, &env->line) == 1)
	{
		if (is_room(env->line))
		{
			add_room(env, create_room(env->line));
			// printf("room %s\n", env->line);
		}
		if (is_link(env->line))
		{
			add_link(env, get_link(env, env->line));
		}
		// print_links(env->links);
		// if (is_command(env->line))
		// 	printf("command %s\n", env->line);
		// if (is_comment(env->line))
		// 	printf("comment %s\n", env->line);
		// if (is_link(env->line))
		// 	printf("link %s\n", env->line);
	}
	print_list(env->rooms);
	print_links(env->links);
}
