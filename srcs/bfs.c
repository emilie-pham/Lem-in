/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/10/07 19:14:17 by epham            ###   ########.fr       */
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
	while (start)
	{
		fullstart = start->rev->flow != 1 ? 0 : 1;
		if (!fullstart)
			break ;
		start = start->next;
	}
	while (end)
	{
		fullend = end->rev->flow != 1 ? 0 : 1;
		if (!fullend)
			break ;
		end = end->next;
	}
	if (fullend || fullstart)
		return (0);
	return (1);
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
		}
		free(env->queue);
	}
	env->queue = NULL;
	env->end_queue = NULL;
	return (1);
}

/*
***     CREATE QUEUE MAILLON AND APPEND IT
*/

void		append_queue(t_env *env, t_link *link, t_room *prev)
{
	t_queue		*last;

	if (!(last = (t_queue*)malloc(sizeof(t_queue))))
		return ;
	last->room = link->dest;
	link->dest->inqueue = 1;
	link->dest->from = link;
	last->room->prev = prev;
	last->prev_flow = link->flow;
	link->dest->weight = link->flow == -1 ? prev->weight - 1 : prev->weight + 1;
	last->next = NULL;
	if (!env->queue)
	{
		env->queue = last;
		env->end_queue = env->queue;
		return ;
	}
	env->end_queue->next = last;
	env->end_queue = last;
}

/*
***     GET LINKS TO ADD TO QUEUE
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
