/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:18:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/15 22:04:16 by anonymous        ###   ########.fr       */
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

t_link	*get_link(t_env *env, char *line)
{
	char	*start;
	char	*end;
	char	*dash;

	if (dash = (ft_strchr(line, '-')))
	{
		start = ft_strsub(line, 0, dash - line);
		printf("start %s\n", start);
		end = ft_strsub(line, dash, ft_strlen(line));
		printf("end %s\n", end);
	}
	return (NULL);
}

void	parse_links(t_env *env)
{
	env->links = NULL;
	while (get_next_line(0, &env->line) == 1)
	{
		if (is_link(env->line))
		{
			get_link(env, env->line);
			add_link(env, get_link(env, env->line));
		}
	}
	print_list(env->links);
}

void	print_links(t_link *head)
{
	t_room *current;

	current = head;
	while (current)
	{
		printf("link	 %d %d\n", );
		current = current->next;
	}
}