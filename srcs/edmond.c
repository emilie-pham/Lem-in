/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anradixt <anradix@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:42:39 by epham             #+#    #+#             */
/*   Updated: 2019/08/01 14:03:52 by anradixt         ###   ########.fr       */
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

	printf("CREATE SOLUTION\n");
	sol = (t_solution *)ft_memalloc(sizeof(t_solution));
	path = (t_path*)ft_memalloc(sizeof(t_path));
	path->room = env->start;
	path->ant_index = 0;
	path->next = NULL;
	sol->path = path;
	if (env->paths)
	{
		head = env->paths;
		while (head->next)
			head = head->next;
		head->next = sol;
	}
	else
		env->paths = sol;
}

/*
***		CREATE PATH
*/

void	create_path(t_env *env, t_room *room)
{
	t_room *current;
	t_path *head;
	t_path *path;
	t_solution *sol;

	printf("CREATE PATH\n");
	sol = env->paths;
	while (sol->next)
		sol = sol->next;
	head = sol->path;
	current = room;
	path = (t_path*)ft_memalloc(sizeof(t_path));
	path->room = current;
	path->ant_index = 0;
	path->next = NULL;
	while (head->next)
		head = head->next;
	head->next = path;
}

/*
***		GET PATH
*/

void	get_path(t_env *env, t_room *room)
{
	t_link *link;
	t_room *current_room;

	link = room->linked_rooms;
	current_room = room;
	while (ft_strcmp(current_room->name, env->end->name) != 0)
	{
		while (link->flow != 1)
			link = link->next;
		current_room = link->dest;
		create_path(env, current_room);
		link = current_room->linked_rooms;
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
			printf("LINK FLOW = 1\n");
			create_path(env, link->dest);
			get_path(env, link->dest);
		}
		else
			printf("LINK FLOW != 1\n");
		link = link->next;
	}
	print_paths(env);
}

/*
***		EDMONDS KARP
*/

int		edmond(t_env *env)
{
	while (bfs(env) == 1)
	{
		printf("UPDATE FLOWS\n");
		update_flows(env);
		printf("GET SOLUTION\n");
		create_solution(env);
		get_solution(env);
	}
	printf("END EDMOND\n");
	return (1);
}
