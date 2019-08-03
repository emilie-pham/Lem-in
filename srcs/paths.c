/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:36:38 by epham             #+#    #+#             */
/*   Updated: 2019/08/03 15:55:37 by epham            ###   ########.fr       */
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
	env->ants_sent = 0;
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
		printf("FREEING ROOM %s FROM PATH\n", path->room->name);
		tmp = path;
		path->room = NULL;
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
		printf("REMOVING PREVIOUS PATH\n");
		while (env->optimal_sol)
		{
			printf("REPLACE BY THIS SOL");
			print_paths(head);
			free_path(env->optimal_sol->path);
			printf("AFTER FREE PATH\n");
			sol = env->optimal_sol;
			env->optimal_sol = env->optimal_sol->next;
			sol->next = NULL;
			printf("BEFORE FREE SOL\n");
			free(sol);
			printf("AFTER FREE SOL\n");
		}
	}
	env->optimal_sol = head;	
}
