/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/16 13:35:18 by yoribeir         ###   ########.fr       */
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
	link->start = start;
	link->end = end;
	link->next = NULL;
	return (link);
}

t_link	*get_link(t_env *env, char *line)
{
	char	*start;
	char	*end;
	char	*dash;
	t_room	*start_room;
	t_room	*end_room;

	if ((dash = (ft_strchr(line, '-'))))
	{
		start = ft_strsub(line, 0, dash - line);
		// printf("start %s\n", start);
		end = ft_strsub(dash + 1, 0, ft_strlen(line));
		// printf("end %s\n", end);
		return (create_link(start_room, end_room));
	}
	return (NULL);
}

void	print_links(t_link *head)
{
	t_link *current;

	current = head;
	while (current)
	{
		printf("link	 %s %s\n", current->start_name, current->end_name);
		current = current->next;
	}
}

void	parse_links(t_env *env)
{
	env->links = NULL;
	while (get_next_line(0, &env->line) == 1)
	{
		printf("%s\n", env->line);
		if (is_link(env->line))
		{
			get_link(env, env->line);
			add_link(env, get_link(env, env->line));
		}
	}
	print_links(env->links);
}
