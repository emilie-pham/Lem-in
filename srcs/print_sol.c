/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:42:11 by epham             #+#    #+#             */
/*   Updated: 2019/08/16 16:44:39 by yoribeir         ###   ########.fr       */
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
***		MOVE ANTS
*/

void	print_ants(t_env *env, t_solution *sol, int *i)
{
	if (!ft_strcmp(sol->path->room->name, env->end->name))
	{
		if (sol->ants_arrived < sol->ants_sent)
		{
			if ((*i)++ != 0)
				printf(" ");
			printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
			sol->ants_arrived++;
		}
	}
	else if (sol->path->ant_index != sol->path->next->ant_index)
	{
		if ((*i)++ != 0)
			printf(" ");
		printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
	}
	sol->path = sol->path->prev;
}

/*
***		UPDATING ANT INDEX FOR EACH NODE
*/

void	move_ants(t_env *env, t_solution *sol, t_path *head, int *i)
{
	while (ft_strcmp(sol->path->room->name, head->next->room->name))
	{
		if (sol->path->prev)
			sol->path->ant_index = sol->path->prev->ant_index;
		print_ants(env, sol, i);
	}
	if (!ft_strcmp(sol->path->room->name, head->next->room->name)
	&& sol->ants_sent < sol->ants)
	{
		sol->path->ant_index = env->next_ant;
		sol->ants_sent++;
		if ((*i)++ != 0)
			printf(" ");
		printf("L%d-%s", sol->path->ant_index, sol->path->room->name);
		(env->next_ant)++;
	}
	sol->path = head;
}

/*
***		PRINT SOLUTION
*/

void	print_sol(t_env *env, t_solution *solution)
{
	int			i;
	t_solution	*sol;
	t_path		*head;

	env->next_ant = 1;
	sol = solution;
	while (env->steps)
	{
		solution = sol;
		i = 0;
		while (solution)
		{
			head = solution->path;
			if (!ft_strcmp(solution->path->room->name, env->start->name))
				solution->path = solution->path->next;
			while (solution->path->ant_index && solution->path->next)
				solution->path = solution->path->next;
			if (!ft_strcmp(head->next->room->name, env->end->name))
				return (print_end(solution));
			move_ants(env, solution, head, &i);
			solution = solution->next;
		}
		(env->steps)--;
		printf("\n");
	}
}
