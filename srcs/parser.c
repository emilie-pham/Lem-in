/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:26:13 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/15 16:39:33 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	parse_ants(t_env *env)
{
	if (get_next_line(0, &env->line) < 1)
	{
		ft_strdel(&env->line);
		ft_error(1);
	}
	else
		add_line(env, create_line(env->line));
	while (is_comment(env->line))
		get_line(env);
	if (!ft_strdigit(env->line))
	{
		ft_strdel(&env->line);
		ft_error(3);
	}
	env->ant_nb = ft_atoi(env->line);
	if (env->ant_nb <= 0)
	{
		ft_strdel(&env->line);
		ft_error(3);
	}
	ft_strdel(&env->line);
}

void	reader(t_env *env, t_room **table)
{
	t_room	*room;

	while (get_next_line(0, &env->line) == 1)
	{
		add_line(env, create_line(env->line));
		if (is_room(env->line))
		{
			room = create_room(env->line);
			insert_hash_table(table, room);
		}
		else if (is_command(env->line))
			parse_startend(env, table);
		else if (is_link(env->line))
			if (!(get_link(env, table, env->line)))
				break ;
		if ((!is_room(env->line)) && !(is_link(env->line))
		&& !(is_comment(env->line)) && !is_command(env->line))
			break ;
		ft_strdel(&env->line);
	}
}

void	parse(t_env *env)
{
	t_room	**table;

	if (!(table = (t_room**)malloc(sizeof(t_room*) * 10007)))
		return ;
	env->table = table;
	init_hashtable(table);
	parse_ants(env);
	reader(env, table);
	if (!env->start || !env->end)
		ft_error(4);
	if (!env->flag_link)
		ft_error(1);
	if (!bfs(env))
		ft_error(5);
}
