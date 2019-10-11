/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:58:29 by epham             #+#    #+#             */
/*   Updated: 2019/10/11 15:25:46 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		KEEP PATH WITH SMALLEST STEP
*/

void		find_smallest_step_path(t_env *env)
{
	int			smallest;
	t_solution	*sol;

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

int			negative_ants(t_env *env, t_solution **negants, t_solution **head)
{
	if ((*negants)->next)
		*head = (*negants)->next;
	env->total_len -= remove_path(env, *negants);
	env->path_nb -= 1;
	if (!env->path_nb || (!(*head) && !env->current_sol))
		return (-2);
	else if (!env->current_sol && *head)
		env->current_sol = *head;
	env->current_sol->steps = check_steps(env);
	return (-1);
}

/*
***		GET NUMBER OF STEPS FOR THIS SOLUTION SYSTEM
*/

int			check_steps(t_env *env)
{
	t_solution	*sol;
	t_solution	*negants;
	t_solution	*newhead;
	int			steps;

	sol = env->current_sol;
	steps = 0;
	env->ants_sent = 0;
	env->shortest_path = NULL;
	env->second_shortest = NULL;
	if ((negants = dispatch_ants(env, env->current_sol)) != NULL)
		return (negative_ants(env, &negants, &newhead));
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
