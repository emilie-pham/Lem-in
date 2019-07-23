/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/23 18:00:23 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	parse_ants(t_env *env)
{
	if (get_next_line(0, &env->line) < 1)
		ft_error(1);
	if (!ft_isdigit(*env->line))
		ft_error(1);
	env->ant_nb = ft_atoi(env->line);
	if (env->ant_nb <= 0)
		ft_error(1);
	printf("ants	%d\n", env->ant_nb);
	ft_strdel(&env->line);
}

void	parse(t_env *env)
{
	env->rooms = NULL;
	env->links = NULL;
	t_room	*room;

	parse_ants(env);
	while (get_next_line(0, &env->line) == 1)
	{
		if (is_room(env->line))
		{
			room = create_room(env->line);
			add_room(env, room);
		}
		if (is_link(env->line))
		{
			// printf("LINK %s\n", env->line);
			add_link(env, get_link(env, env->line));
		}
		if (is_command(env->line))
		{
			// printf("COMMAND %s\n", env->line);
			parse_startend(env);
		}
		// if (is_comment(env->line))
			// printf("comment %s\n", env->line);
		if (!is_room(env->line) && !is_link(env->line) && !is_comment(env->line)
			&& !is_command(env->line))
			break ;
	}
	print_rooms(env->rooms);
	// print_links(env->links);
}
