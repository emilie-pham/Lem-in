/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:42:39 by epham             #+#    #+#             */
/*   Updated: 2019/08/02 16:48:29 by epham            ###   ########.fr       */
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

	// printf("CREATE PATHLINK with room %s\n", room->name);
	pathlink = (t_path*)ft_memalloc(sizeof(t_path));
	pathlink->room = room;
	pathlink->ant_index = 0;
	pathlink->next = NULL;
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

t_solution	*append_sol(t_solution *head, t_solution *sol)
{
	t_solution *last;

	last = head;
	while (last->next)
		last = last->next;
	last->next = sol;
	return (head);
}

/*
***		NEW PATH IN SAME SOLUTION SYSTEM
*/

t_solution	*create_sol(t_env *env, t_solution *current, t_room *next)
{
	t_solution *head;
	t_solution *new;

	printf("NEW PATH IN SOLUTION SYSTEM\n");
	head = current;
	if (head)
	{
		printf("HEAD EXISTS\n");
		new = (t_solution *)ft_memalloc(sizeof(t_solution));
	}
	else
		new = head;
	new->ants = 0;
	new->pathlen = 0;
	new->next = NULL;
	new->path = get_path(env, next, new);
	while (head->next)
		head = head->next;
	head->next = new;
	print_paths(head);
	return (head);
}

int		sollen(t_solution *sol)
{
	int i;

	i = 0;
	while (sol)
	{
		i += 1;
		sol = sol->next;
	}
	return (i);
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
		env->path_nb = 0;
		env->total_len = 0;
		update_flows(env);
		printf("NEW SOLUTION SYSTEM\n");
		link = env->start->linked_rooms;
		while (link)
		{
			if (link->flow == 1)
			{
				if (first == 0)
				{
					current_sol = (t_solution *)ft_memalloc(sizeof(t_solution));
					current_sol->path = NULL;
					current_sol->ants = 0;
					current_sol->pathlen = 0;
					current_sol->next = NULL;
					head = current_sol;
					first = 1;
				}
				else
					current_sol = create_sol(env, head, link->dest);
				env->path_nb += 1;
			}
			link = link->next;
		}
		printf("NUMBER OF PATHS : %d VS SOLLEN %d\n", env->path_nb, sollen(current_sol));
		printf("TOTAL LENGTH : %d\n", env->total_len);
		ants_to_send(env, current_sol);
	}
	printf("END EDMOND\n");
	return (1);
}
