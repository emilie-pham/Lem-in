/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/10/08 15:27:10 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->line = NULL;
	env->ant_nb = 0;
	env->flag_link = 0;
	env->links = NULL;
	env->start = NULL;
	env->end = NULL;
	env->queue = NULL;
	env->read = NULL;
	env->end_queue = env->queue;
	env->optimal_sol = NULL;
	env->path_nb = 0;
	env->total_len = 0;
	env->ants_sent = 0;
	env->steps = 2147483647;
	env->shortest_path = NULL;
	env->second_shortest = NULL;
	return (env);
}

int				main(int ac, char **av)
{
	t_env	*env;

	(void)ac;
	(void)av;
	if (!(env = init_env()))
		return (0);
	parse(env);
	print_map(env);
	if (edmond(env) != 0)
		print_sol(env, env->optimal_sol);
	print_paths(env->optimal_sol);
	free(env);
	return (0);
}
