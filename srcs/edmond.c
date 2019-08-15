/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:42:39 by epham             #+#    #+#             */
/*   Updated: 2019/08/15 19:32:04 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		UPDATE FLOWS
*/

static void		update_flows(t_env *env)
{
	t_link	*link;
	t_room	*current;

	current = env->end;
	while (ft_strcmp(current->name, env->start->name))
	{
		link = current->linked_rooms;
		while (link)
		{
			if (!ft_strcmp(link->dest->name, current->prev->name))
				break ;
			link = link->next;
		}
		link->flow -= 1;
		link->rev->flow += 1;
		current = current->prev;
	}
}

/*
***		REPLACE OPTIMAL SOLUTION
*/

static void		update_solution(t_env *env)
{
	t_solution *sol;

	free_sol(env->optimal_sol);
	env->optimal_sol = env->current_sol;
	env->steps = env->current_sol->steps;
}


/*
***		RESET INPATH
*/

static void		reset_inpath(t_solution *solution)
{
	t_solution	*head_sol;
	t_path		*head_path;

	if (solution)
	{
		head_sol = solution;
		while (solution)
		{
			head_path = solution->path;
			while (solution->path)
			{
				solution->path->room->inpath = 0;
				solution->path = solution->path->next;
			}
			solution->path = head_path;
			solution = solution->next;
		}
		solution = head_sol;
	}
	
}

/*
***		CHECK ALL LINKS FROM START
*/

static int		check_start_links(t_env *env, int first)
{
	t_solution	*current_sol;
	t_link		*link;

	link = env->start->linked_rooms;
	while (link)
	{
		if (link->flow == 1/* && link->dest->inpath == 0*/)
		{
			if (first == 0 && (env->current_sol = create_solution(env, link->dest)))
			{
				first = 1;
				env->path_nb += 1;
			}
			else if (first == 1 && (current_sol = create_solution(env, link->dest)))
				append_sol(env, current_sol);
		}
		link = link->next;
	}
	return (first);
}

/*
***		EDMONDS KARP
*/

int				edmond(t_env *env)
{
	int			first;
	int			steps;

	t_solution *sol;

	while (bfs(env) == 1)
	{
		env->path_nb = 0;
		env->total_len = 0;
		env->ants_sent = 0;
		update_flows(env);
		first = 0;
		first = check_start_links(env, first);
		if (first == 0 && !env->current_sol && !env->optimal_sol)
			return (0);
		else if (env->current_sol && first)
		{
			reset_inpath(env->current_sol);
			if ((steps = check_steps(env)) < 0)
				continue ;
			env->current_sol->steps = steps;
			if (env->current_sol->steps < env->steps)
				update_solution(env);
			else
				free_sol(env->current_sol);
		}
	}
	return (1);
}
