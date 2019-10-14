/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:12:42 by epham             #+#    #+#             */
/*   Updated: 2019/10/14 19:13:29 by epham            ###   ########.fr       */
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

void	free_sol(t_sol **sol)
{
	t_sol	*tmp;
	t_sol	**head;

	head = sol;
	if (*sol)
	{
		while (*sol)
		{
			free_path((*sol)->path);
			tmp = *sol;
			*sol = (*sol)->next;
			// (*sol)->next = NULL;
			tmp->next = NULL;
			free(tmp);
			// *sol =tmp;
		}
	}
	*head = NULL;
	head = NULL;
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
	if (env->queue)
		free_queue(env);
	if (env->current_sol)
		free_sol(&env->current_sol);
	if (env->optimal_sol)
		free_sol(&env->optimal_sol);
}
