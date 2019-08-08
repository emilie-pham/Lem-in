/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:36:38 by epham             #+#    #+#             */
/*   Updated: 2019/08/08 14:52:58 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	dispatch_leftover(t_solution *shortest, t_solution *second, t_env *env)
{
	int		difflen;
	int		sumlen;
	int		leftover;
	int		leftshort;
	int		leftsecond;

	leftover = env->ant_nb - env->ants_sent;	
	if (second)
	{
		difflen = second->pathlen - shortest->pathlen;
		sumlen = second->pathlen + shortest->pathlen;
	}
	if (!second || difflen == 0 || leftover <= difflen)
	{
		shortest->ants += leftover;
		env->ants_sent += leftover;
	}
	else if (leftover > difflen && second)
	{
		leftshort = (leftover + sumlen) / 2 - shortest->pathlen;
		leftsecond = (leftover + sumlen) / 2 - second->pathlen;
		shortest->ants += leftshort;
		second->ants += leftsecond;
		env->ants_sent += leftshort + leftsecond;
	}
}

/*
***		DISTRIBUTES ANTS OVER ALL PATHS OF SOLUTION
*/

void	dispatch_ants(t_env *env, t_solution *head)
{
	t_solution	*sol;
	int			min;
	int			second;

	min = 2147483647;
	second = 2147483647;
	sol = head;
	while (sol)
	{
		sol->ants = (env->ant_nb + env->total_len)
		/ env->path_nb - sol->pathlen;
		env->ants_sent += sol->ants;
		if (sol->pathlen < min)
		{
			env->shortest_path = sol;
			min = sol->pathlen;
		}
		else if (sol->pathlen >= min && sol->pathlen < second)
		{
			env->second_shortest = sol;
			second = sol->pathlen;
		}
		sol = sol->next;
	}
	sol = head;
}

/*
***		GET NUMBER OF STEPS FOR THIS SOLUTION SYSTEM
*/

int		check_steps(t_env *env, t_solution *head)
{
	t_solution	*sol;
	int			steps;

	sol = head;
	steps = 0;
	env->ants_sent = 0;
	env->shortest_path = NULL;
	env->second_shortest = NULL;
	dispatch_ants(env, head);
	while (env->ants_sent < env->ant_nb)
		dispatch_leftover(env->shortest_path, env->second_shortest, env);
	while (sol)
	{
		sol->steps = sol->pathlen + sol->ants - 1;
		if (sol->steps > steps)
			steps = sol->steps;
		sol = sol->next;
	}
	sol = head;
	return (steps);
}

/*
***		FREE PATH
*/

void	free_path(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		tmp = path;
		path->room = NULL;
		path = path->next;
		tmp->next = NULL;
		free(tmp);
	}
}

/*
***		REPLACE OPTIMAL SOLUTION
*/

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
