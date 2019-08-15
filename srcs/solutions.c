/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:22:01 by epham             #+#    #+#             */
/*   Updated: 2019/08/15 19:37:11 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		NEW PATH IN SAME SOLUTION SYSTEM
*/

t_solution		*create_solution(t_env *env, t_room *next)
{
	t_solution *new;

	new = (t_solution*)ft_memalloc(sizeof(t_solution));
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
	t_solution	*newhead;
	int			min;
	int			second;

	min = 2147483647;
	second = 2147483647;
	sol = head;
	while (sol)
	{
		sol->ants = (env->ant_nb + env->total_len)
		/ env->path_nb - sol->pathlen;
		if (sol->ants < 0)
			return (sol);
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
	return (NULL);
}

void			dispatch_leftover(t_solution *one, t_solution *two, t_env *env)
{
	int		difflen;
	int		sumlen;
	int		leftover;
	int		leftshort;
	int		leftsecond;

	leftover = env->ant_nb - env->ants_sent;
	if (two)
	{
		difflen = two->pathlen - one->pathlen;
		sumlen = two->pathlen + one->pathlen;
	}
	if (!two || difflen == 0 || leftover <= difflen)
	{
		one->ants += leftover;
		env->ants_sent += leftover;
	}
	else if (leftover > difflen && two)
	{
		leftshort = (leftover + sumlen) / 2 - one->pathlen;
		leftsecond = (leftover + sumlen) / 2 - two->pathlen;
		one->ants += leftshort;
		two->ants += leftsecond;
		env->ants_sent += leftshort + leftsecond;
	}
}
