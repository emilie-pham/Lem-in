/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:12:42 by epham             #+#    #+#             */
/*   Updated: 2019/10/14 18:55:15 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
		tmp = NULL;
	}
}

/*
***		FREE SOL
*/

void	free_sol(t_sol *sol)
{
	t_sol *tmp;

	if (sol)
	{
		while (sol)
		{
			free_path(sol->path);
			tmp = sol;
			sol = sol->next;
			tmp->next = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
}

void	free_links(t_link *links)
{
	t_link	*tmp;
	t_link	*tmp1;

	tmp = links;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
		tmp1 = NULL;
	}
}

void	free_queue(t_env *env)
{
	t_queue	*head;
	t_queue	*tmp;

	if (env->queue)
	{
		head = env->queue;
		while (head)
		{
			head->room->prev = NULL;
			head->room->visited = 0;
			head->room->inqueue = 0;
			head->room->weight = 0;
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
	env->queue = NULL;
	env->end_queue = NULL;
}

void	free_env(t_env *env)
{
	ft_strdel(&env->line);
	// if (env->read)
		// free_lines(env->read);
	// if (env->table)
		// free_table(env->table);
	if (env->queue)
		free_queue(env);
	// if (env->current_sol)
	// 	free_sol(env->current_sol);
	if (env->optimal_sol)
		free_sol(env->optimal_sol);
}

