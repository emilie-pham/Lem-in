/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:17:16 by epham             #+#    #+#             */
/*   Updated: 2019/10/10 13:18:41 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
***		INSERT TO QUEUE IN MIDDLE BUT AFTER PREV
*/

void		insert_after_queue(t_env *env, t_link *link, t_room *prev)
{
	t_queue		*insert;
	t_queue		*find;
	t_queue		*tmp;

	find = env->queue;
	if (!(insert = (t_queue*)malloc(sizeof(t_queue))))
		return ;
	insert->room = link->dest;
	link->dest->inqueue = 1;
	link->dest->from = link;
	insert->room->prev = prev;
	insert->prev_flow = link->flow;
	link->dest->weight = link->flow == -1 ? prev->weight - 1 : prev->weight + 1;
	insert->next = NULL;
	if (!env->queue)
	{
		env->queue = insert;
		env->end_queue = env->queue;
		return ;
	}
	while (find->next && ft_strcmp(find->room->name, prev->name))
		find = find->next;
	tmp = find->next;
	find->next = insert;
	insert->next = tmp;
}

/*
***		INSERT TO QUEUE IN MIDDLE BUT BEFORE PREV
*/

void		insert_before_queue(t_env *env, t_link *link, t_room *prev)
{
	t_queue		*insert;
	t_queue		*find;
	t_queue		*tmp;

	find = env->queue;
	if (!(insert = (t_queue*)malloc(sizeof(t_queue))))
		return ;
	insert->room = link->dest;
	link->dest->inqueue = 1;
	link->dest->from = link;
	insert->room->prev = prev;
	insert->prev_flow = link->flow;
	link->dest->weight = link->flow == -1 ? prev->weight - 1 : prev->weight + 1;
	insert->next = NULL;
	if (!env->queue)
	{
		env->queue = insert;
		env->end_queue = env->queue;
		return ;
	}
	while (find->next && ft_strcmp(find->next->room->name, prev->name))
		find = find->next;
	tmp = find->next;
	find->next = insert;
	insert->next = tmp;
}
