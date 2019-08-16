/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:36:38 by epham             #+#    #+#             */
/*   Updated: 2019/08/16 12:45:41 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		NEW PATHLINK
*/

t_path		*create_pathlink(t_env *env, t_room *room)
{
	t_path *pathlink;

	if (room->inpath != 0 && (ft_strcmp(room->name, env->start->name)
	&& ft_strcmp(room->name, env->end->name)))
	{
		// printf("start : %s || room : %s || room->inpath = %d\n", env->start->name, room->name, room->inpath);
		return (NULL);
	}
	room->inpath = 1;
	pathlink = (t_path*)ft_memalloc(sizeof(t_path));
	pathlink->room = room;
	pathlink->ant_index = 0;
	pathlink->next = NULL;
	pathlink->prev = NULL;
	return (pathlink);
}

/*
***		GET ONE PATH IN SOLUTION SYSTEM
*/

t_path		*get_path(t_env *env, t_room *next, t_solution *sol)
{
	t_path *path;
	t_path *head;
	t_link *link;

	if (next->inpath == 0)
	{
		path = create_pathlink(env, env->start);
		head = path;
		if (!(path->next = create_pathlink(env, next)))
			return (NULL);
		path = path->next;
		link = next->linked_rooms;
		sol->pathlen += 1;
		while (ft_strcmp(path->room->name, env->end->name))
		{
			while (link->flow != 1)
				link = link->next;
			if (!(path->next = create_pathlink(env, link->dest)))
			{
				free_path(head);
				return (NULL);
			}
			path->next->prev = path;
			path = path->next;
			link = path->room->linked_rooms;
			sol->pathlen += 1;
		}
		env->total_len += sol->pathlen;
		return (head);
	}
	return (NULL);
}

/*
***		REMOVE PATH THAT IS TOO LONG
*/

int			remove_path(t_env *env, t_solution *remove)
{
	t_solution	*current;
	t_solution	*prev;
	int			pathlen;

	current = env->current_sol;
	prev = env->current_sol;
	while (current != remove && current->next)
	{
		prev = current;
		current = current->next;
	}
	pathlen = current->pathlen;
	free_path(current->path);
	if (current == env->current_sol && current->next)
		env->current_sol = current->next;
	else if (current->next)
		prev->next = current->next;
	else
		prev->next = NULL;
	free(current);
	return (pathlen);
}

/*
***		GET NUMBER OF STEPS FOR THIS SOLUTION SYSTEM
*/

int			check_steps(t_env *env)
{
	t_solution	*sol;
	t_solution	*negants;
	t_solution	*newhead;
	int			steps;

	sol = env->current_sol;
	steps = 0;
	env->ants_sent = 0;
	env->shortest_path = NULL;
	env->second_shortest = NULL;
	if ((negants = dispatch_ants(env, env->current_sol)) != NULL)
	{
		if (negants->next)
			newhead = negants->next;
		env->total_len -= remove_path(env, negants);
		env->path_nb -= 1;
		if (!env->path_nb || (!newhead && !env->current_sol))
			return (-2);
		else if (!env->current_sol && newhead)
			env->current_sol = newhead;
		env->current_sol->steps = check_steps(env);
		return (-1);
	}
	while (env->ants_sent < env->ant_nb)
		dispatch_leftover(env->shortest_path, env->second_shortest, env);
	while (sol)
	{
		sol->steps = sol->pathlen + sol->ants - 1;
		if (sol->steps > steps)
			steps = sol->steps;
		sol = sol->next;
	}
	sol = env->current_sol;
	return (steps);
}
