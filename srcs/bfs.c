/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/10/10 14:00:17 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			check_start_end(t_env *env)
{
	t_link		*start;
	t_link		*end;
	int			fullstart;
	int			fullend;

	start = env->start->linked_rooms;
	end = env->end->linked_rooms;
	fullend = 1;
	fullstart = 1;
	while (start && end)
	{
		fullstart = start->rev->flow != 1 ? 0 : 1;
		fullend = end->rev->flow != 1 ? 0 : 1;
		if (fullstart)
			start = start->next;
		if (fullend)
			end = end->next;
		if (!fullstart && !fullend)
			return (1);
	}
	return (0);
}

/*
***     INITIALIZE BFS : PREV TO NULL AND VISITED TO 0
*/

int			initialize_bfs(t_env *env)
{
	t_queue		*head;
	t_queue		*tmp;
	t_link		*endlinks;

	endlinks = env->end->linked_rooms;
	if (!check_start_end(env))
		return (0);
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
	return (1);
}

/*
***     GET QUEUE FROM ROOM
*/

void		get_queue(t_env *env, t_room *room)
{
	t_link		*currlink;
	int			weight;

	weight = 0;
	room->visited = 1;
	currlink = room->linked_rooms;
	if (remontada(env, room, currlink) == 1)
		return ;
	while (currlink)
	{
		weight = currlink->flow == -1 ? room->weight - 1 : room->weight + 1;
		if (currlink->dest->inqueue == 0 && currlink->flow != 1)
			append_queue(env, currlink, room);
		else if (ft_strcmp(currlink->dest->name, env->start->name)
		&& ft_strcmp(currlink->dest->name, env->end->name)
		&& currlink->dest->inqueue && currlink->dest->weight > weight)
		{
			if (check_change_source(env, currlink->dest, room) == 1)
				change_source(env, currlink->dest, currlink, room);
		}
		currlink = currlink->next;
	}
}

/*
***     BFS
*/

int			bfs(t_env *env)
{
	t_room		*current;
	t_queue		*queue;

	current = env->start;
	if (initialize_bfs(env))
	{
		current->visited = 1;
		get_queue(env, env->start);
		if (!env->queue)
			return (0);
		queue = env->queue;
		current = queue->room;
		while (ft_strcmp(current->name, env->end->name))
		{
			get_queue(env, current);
			if (queue->next)
				queue = queue->next;
			else
				return (0);
			current = queue->room;
		}
		return (1);
	}
	return (0);
}
