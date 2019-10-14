/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:58:29 by epham             #+#    #+#             */
/*   Updated: 2019/10/14 17:25:42 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		KEEP PATH WITH SMALLEST STEP
*/

void		find_smallest_step_path(t_env *env)
{
	int			smallest;
	t_sol		*sol;

	sol = env->current_sol;
	smallest = 2147483647;
	while (sol)
	{
		sol->steps = sol->pathlen + sol->ants - 1;
		if (sol->steps < smallest)
		{
			env->shortest_path = sol;
			smallest = sol->steps;
		}
		sol = sol->next;
	}
	sol = env->current_sol;
	env->shortest_path->ants += 1;
	env->ants_sent += 1;
}

/*
***		NEGATIVE ANTS
*/

int			negative_ants(t_env *env, t_sol **negants)
{
	t_sol	*newhead;

	if ((*negants)->next)
		newhead = (*negants)->next;
	env->total_len -= (*negants)->pathlen;
	remove_path(env, *negants);
	env->path_nb -= 1;
	if (!env->path_nb || (!newhead && !env->current_sol))
		return (-2);
	else if (!env->current_sol && newhead)
		env->current_sol = newhead;
	env->current_sol->steps = check_steps(env);
	return (-1);
}

/*
***		GET NUMBER OF STEPS FOR THIS SOLUTION SYSTEM
*/

int			check_steps(t_env *env)
{
	t_sol	*sol;
	t_sol	*negants;
	int		steps;

	sol = env->current_sol;
	steps = 0;
	env->ants_sent = 0;
	env->shortest_path = NULL;
	env->second_shortest = NULL;
	if ((negants = dispatch_ants(env, env->current_sol)) != NULL)
		return (negative_ants(env, &negants));
	while (env->ants_sent < env->ant_nb)
		find_smallest_step_path(env);
	while (sol)
	{
		sol->steps = sol->pathlen + sol->ants - 1;
		if (sol->steps > steps)
			steps = sol->steps;
		sol = sol->next;
	}
	sol = env->current_sol;
	return (steps);
}
