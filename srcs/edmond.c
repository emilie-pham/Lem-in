/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:42:39 by epham             #+#    #+#             */
/*   Updated: 2019/07/30 21:24:28 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		FIND CORRESPONDING LINK
*/

t_link	*findlink(t_room *current, t_room *prev)
{
	t_link	*link;

	link = current->linked_rooms;
	while (link)
	{
		if (ft_strcmp(link->dest->name, prev->name) == 0)
			return (link);
		link = link->next;
	}
	return (NULL);
}

/*
***		UPDATE FLOWS
*/

void	update_flows(t_env *env)
{
	t_link	*link;
	t_room	*current;

	current = env->end;
	while (current != env->start)
	{
		link = findlink(current, current->prev);
		link->flow -= 1;
		link->rev->flow += 1;
		current = current->prev;
	}
}

/*
***		CREATE SOLUTION
*/

void	create_solution(t_env *env)
{
	t_solution	*sol;
	t_solution	*head;
	t_path		*path;

	sol = (t_solution *)ft_memalloc(sizeof(t_solution *));
	path = (t_path*)ft_memalloc(sizeof(t_path*));
	path->room = env->start;
	path->ant_index = 0;
	path->next = NULL;
	sol->path = path;
	head = env->paths;
	while (head)
		head = head->next;
	head = sol;
}

/*
***		CREATE PATH
*/

void	create_path(t_env *env, t_room *room)
{
	t_room *current;
	t_path *head;
	t_path *path;
	t_link *link;

	head = env->paths->path;
	current = room;
	path = (t_path*)ft_memalloc(sizeof(t_path*));
	path->room = current;
	path->ant_index = 0;
	path->next = NULL;
	link = current->linked_rooms;
	while (current != env->end)
	{
		if (link->flow == 1)
		{
			path->next = (t_path*)ft_memalloc(sizeof(t_path*));
			path = path->next;
			path->room = current;
			path->ant_index = 0;
			path->next = NULL;
			current = link->dest;
			link = current->linked_rooms;
		}
		else
			link = link->next;
	}
}

/*
***		GET PATHS SOLUTION SYSTEM
*/

void	get_solution(t_env *env)
{
	t_link		*link;

	link = env->start->linked_rooms;
	while (link)
	{
		if (link->flow == 1)
		{
			create_solution(env);
			create_path(env, link->dest);
		}
		link = link->next;
	}
}

/*
***		EDMONDS KARP
*/

int		edmond(t_env *env)
{
	while (bfs(env) == 1)
	{
		update_flows(env);
		get_solution(env);
	}
	return (1);
}
