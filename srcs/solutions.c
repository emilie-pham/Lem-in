/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:22:01 by epham             #+#    #+#             */
/*   Updated: 2019/10/11 18:47:32 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		NEW PATH IN SAME SOLUTION SYSTEM
*/

t_solution		*create_solution(t_env *env, t_room *next)
{
	t_solution *new;

	if (!(new = (t_solution*)malloc(sizeof(t_solution))))
		return (NULL);
	new->ants = 0;
	new->ants_sent = 0;
	new->ants_arrived = 0;
	new->pathlen = 0;
	new->steps = 0;
	new->next = NULL;
	if (!(new->path = get_path(env, next, new)))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

/*
***		APPEND SOLUTION TO HEAD
*/

void			append_sol(t_env *env, t_solution *new)
{
	t_solution *first;

	first = env->current_sol;
	while (env->current_sol->next)
		env->current_sol = env->current_sol->next;
	env->current_sol->next = new;
	env->current_sol = first;
	env->path_nb += 1;
}

/*
***		DISTRIBUTES ANTS OVER ALL PATHS OF SOLUTION
*/

t_solution		*dispatch_ants(t_env *env, t_solution *head)
{
	t_solution	*sol;

	sol = head;
	while (sol)
	{
		sol->ants = (env->ant_nb + env->total_len)
		/ env->path_nb - sol->pathlen;
		if (sol->ants < 0)
			return (sol);
		env->ants_sent += sol->ants;
		sol = sol->next;
	}
	sol = head;
	return (NULL);
}

/*
***		REPLACE OPTIMAL SOLUTION
*/

void			update_solution(t_env *env)
{
	free_sol(env->optimal_sol);
	env->optimal_sol = env->current_sol;
	env->steps = env->current_sol->steps;
}
