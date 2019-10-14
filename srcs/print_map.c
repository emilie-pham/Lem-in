/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:28:40 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/14 17:40:56 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_line		*create_line(char *content)
{
	t_line		*line;

	if (!(line = (t_line *)ft_memalloc(sizeof(t_line))))
		return (NULL);
	line->line = ft_strdup(content);
	line->next = NULL;
	return (line);
}

void		add_line(t_env *env, t_line *line)
{
	t_line			*current;
	static t_line	*tail;

	current = env->read;
	if (!current)
	{
		env->read = line;
		tail = line;
	}
	else
	{
		tail->next = line;
		tail = line;
	}
}

void		get_line(t_env *env)
{
	get_next_line(0, &env->line);
	add_line(env, create_line(env->line));
}

void		print_map(t_env *env)
{
	t_line	*current;

	current = env->read;
	while (current)
	{
		ft_putendl(current->line);
		current = current->next;
	}
	write(1, "\n", 1);
}

void		free_lines(t_line *line)
{
	t_line *tmp;
	t_line *tmp1;

	tmp = line;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1->line);
		free(tmp1);
		tmp1 = NULL;
	}
}
