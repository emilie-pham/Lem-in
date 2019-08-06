/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:42:11 by epham             #+#    #+#             */
/*   Updated: 2019/08/06 13:20:07 by epham            ###   ########.fr       */
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
***		UPDATING ANT INDEX FOR EACH NODE
*/

void	next_step(t_solution *sol, t_path *head, int *next_ant, t_room *end)
{
	while (ft_strcmp(sol->path->room->name, head->next->room->name))
	{
		if (sol->path->prev)
			sol->path->ant_index = sol->path->prev->ant_index;
		if (!ft_strcmp(sol->path->room->name, end->name))
		{
			if (sol->ants_arrived < sol->ants_sent)
			{
				printf("L%d-%s ", sol->path->ant_index, sol->path->room->name);
				sol->ants_arrived++;
			}
		}
		else if (sol->path->ant_index != sol->path->next->ant_index)
			printf("L%d-%s ", sol->path->ant_index, sol->path->room->name);
		sol->path = sol->path->prev;
	}
	if (!ft_strcmp(sol->path->room->name, head->next->room->name)
	&& sol->ants_sent < sol->ants)
	{
		sol->path->ant_index = *next_ant;
		sol->ants_sent++;
		(*next_ant)++;
		printf("L%d-%s ", sol->path->ant_index, sol->path->room->name);
	}
}

/*
***		PRINT SOLUTION
*/

void	print_sol(t_solution *solution, t_room *start, t_room *end, int *steps)
{
	int			next_ant;
	t_solution	*sol;
	t_path		*head;

	next_ant = 1;
	sol = solution;
	while (*steps)
	{
		solution = sol;
		while (solution)
		{
			head = solution->path;
			if (!ft_strcmp(solution->path->room->name, start->name))
				solution->path = solution->path->next;
			while (solution->path->ant_index && solution->path->next)
				solution->path = solution->path->next;
			if (!ft_strcmp(head->next->room->name, end->name))
				return (print_end(solution));
			next_step(solution, head, &next_ant, end);
			solution->path = head;
			solution = solution->next;
		}
		(*steps)--;
		printf("\n");
	}
}
