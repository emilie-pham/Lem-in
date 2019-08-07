/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:42:39 by epham             #+#    #+#             */
/*   Updated: 2019/08/07 17:27:59 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
		link = current->linked_rooms;
		while (link)
		{
			if (ft_strcmp(link->dest->name, current->prev->name) == 0)
				break ;
			link = link->next;
		}
		link->flow -= 1;
		link->rev->flow += 1;
		current = current->prev;
	}
}

/*
***		NEW PATHLINK
*/

t_path		*create_pathlink(t_room *room)
{
	t_path *pathlink;

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

	path = create_pathlink(env->start);
	head = path;
	path->next = create_pathlink(next);
	path = path->next;
	link = next->linked_rooms;
	sol->pathlen += 1;
	while (ft_strcmp(path->room->name, env->end->name) != 0)
	{
		while (link->flow != 1)
			link = link->next;
		path->next = create_pathlink(link->dest);
		path->next->prev = path;
		path = path->next;
		link = path->room->linked_rooms;
		sol->pathlen += 1;
	}
	env->total_len += sol->pathlen;
	return (head);
}

/*
***		APPEND SOLUTION TO HEAD
*/

void	append_sol(t_solution *head, t_solution *sol)
{
	t_solution *first;

	first = head;
	while (head->next)
		head = head->next;
	head->next = sol;
	head = first;
}

/*
***		NEW PATH IN SAME SOLUTION SYSTEM
*/

t_solution	*create_solution(t_env *env, t_room *next)
{
	t_solution *new;

	new = (t_solution*)ft_memalloc(sizeof(t_solution));
	new->ants = 0;
	new->ants_sent = 0;
	new->ants_arrived = 0;
	new->pathlen = 0;
	new->steps = 0;
	new->next = NULL;
	new->path = get_path(env, next, new);
	return (new);
}

/*
***		EDMONDS KARP
*/

int		edmond(t_env *env)
{
	t_solution	*current_sol;
	t_solution	*head;
	t_link		*link;
	int			first;

	first = 0;
	while (bfs(env) == 1)
	{
		// printf("BFS\n");
		env->path_nb = 0;
		env->total_len = 0;
		env->ants_sent = 0;
		update_flows(env);
		link = env->start->linked_rooms;
		first = 0;
		while (link)
		{
			if (link->flow == 1)
			{
				if (first == 0)
				{
					head = create_solution(env, link->dest);
					first = 1;
				}
				else
				{
					current_sol = create_solution(env, link->dest);
					append_sol(head, current_sol);
				}
				env->path_nb += 1;
			}
			link = link->next;
		}
		head->steps = check_steps(env, head);
		if (head->steps < env->steps)
		{
			update_solution(env, head);
			// print_paths(env->optimal_sol);
			env->steps = head->steps;
		}
		// print_paths(head);
	}
	if (first == 0)
		return (0);
	return (1);
}
