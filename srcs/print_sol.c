/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:42:11 by epham             #+#    #+#             */
/*   Updated: 2019/08/14 14:43:20 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		CASE OF START END
*/

void	print_end(t_solution *sol)
{
	int i;

	i = 1;
	while (i <= sol->ants)
	{
		printf("L%d-%s\n", i, sol->path->room->name);
		i++;
	}
}

/*
***		ARRIVING ANTS
*/

void	print_ants(t_env *env, t_solution *sol, int *i)
{
	if (!ft_strcmp(sol->path->room->name, env->end->name))
	{
		if (sol->ants_arrived < sol->ants_sent)
		{
			if ((*i)++ == 0 && sol == env->optimal_sol)
				printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
			else
				printf(" L%d-%s", sol->path->ant_index, sol->path->room->name);
			sol->ants_arrived++;
		}
	}
	else if (sol->path->ant_index != sol->path->next->ant_index)
	{
		if ((*i)++ == 0 && sol == env->optimal_sol)
			printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
		else
			printf(" L%d-%s", sol->path->ant_index, sol->path->room->name);
	}
	sol->path = sol->path->prev;
}

/*
***		UPDATING ANT INDEX FOR EACH NODE
*/

void	next_step(t_env *env, t_solution *sol, t_path *head, int *next_ant)
{
	int	i;

	i = 0;
	while (ft_strcmp(sol->path->room->name, head->next->room->name))
	{
		if (sol->path->prev)
			sol->path->ant_index = sol->path->prev->ant_index;
		print_ants(env, sol, &i);
	}
	if (!ft_strcmp(sol->path->room->name, head->next->room->name)
	&& sol->ants_sent < sol->ants)
	{
		sol->path->ant_index = *next_ant;
		sol->ants_sent++;
		if (i++ == 0 && sol == env->optimal_sol)
			printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
		else
			printf(" L%d-%s", sol->path->ant_index, sol->path->room->name);
		(*next_ant)++;
	}
}

/*
***		PRINT SOLUTION
*/

void	print_sol(t_env *env, t_solution *solution)
{
	int			next_ant;
	t_solution	*sol;
	t_path		*head;

	next_ant = 1;
	sol = solution;
	while (env->steps)
	{
		solution = sol;
		while (solution)
		{
			head = solution->path;
			if (!ft_strcmp(solution->path->room->name, env->start->name))
				solution->path = solution->path->next;
			while (solution->path->ant_index && solution->path->next)
				solution->path = solution->path->next;
			if (!ft_strcmp(head->next->room->name, env->end->name))
				return (print_end(solution));
			next_step(env, solution, head, &next_ant);
			solution->path = head;
			solution = solution->next;
		}
		(env->steps)--;
		printf("\n");
	}
}
