/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anradixt <anradix@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:36:38 by epham             #+#    #+#             */
/*   Updated: 2019/08/02 22:21:48 by anradixt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		check_steps(t_env *env, t_solution *head)
{
	t_solution *sol;
	int			min;
	int			steps;

	sol = head;
	min = 2147483647;
	steps = 0;
	while (sol)
	{
		sol->ants = (env->ant_nb + env->total_len) / env->path_nb - sol->pathlen;
		env->ants_sent += sol->ants;
		if (sol->pathlen < min)
			env->shortest_path = sol;
		sol = sol->next;
	}
	if (env->ants_sent < env->ant_nb)
		env->shortest_path->ants += env->ant_nb - env->ants_sent;
	sol = head;
	while (sol)
	{
		// printf("NUMBER OF ANTS FOR THIS PATH : %d\n", sol->ants);
		sol->steps = sol->pathlen + sol->ants - 1;
		if (sol->steps > steps)
			steps = sol->steps;
		sol = sol->next;
	}
	// printf("STEPS FOR THIS SOLUTION SYSTEM : %d\n", steps);
	return (steps);
}

void	free_path(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		path->room = NULL;
		tmp = path;
		path = path->next;
		tmp->next = NULL;
		free(tmp);
	}
}

void	update_solution(t_env *env, t_solution *head)
{
	t_solution *sol;
	
	if (env->optimal_sol)
	{
		while (env->optimal_sol)
		{
			free_path(env->optimal_sol->path);
			sol = env->optimal_sol;
			env->optimal_sol = env->optimal_sol->next;
			sol->next = NULL;
			free(sol);
		}
	}
	env->optimal_sol = head;	
}
