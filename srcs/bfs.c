/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/10/02 11:16:01 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int        check_start_end(t_env *env)
{
    t_link      *start;
    t_link      *end;
    int         fullstart;
    int         fullend;

    start = env->start->linked_rooms;
    end = env->end->linked_rooms;
    fullend = 1;
    fullstart = 1;
    while (start)
    {
        if (start->rev->flow != 1)
        {
            fullstart = 0;
            break;
        }
        start = start->next;
    }
    while (end)
    {
        if (end->rev->flow != 1)
        {
            fullend = 0;
            break;
        }
        end = end->next;
    }
    if (fullend || fullstart)
        return (0);
    return (1);
}

/*
***     INITIALIZE BFS : PREV TO NULL AND VISITED TO 0
*/

int        initialize_bfs(t_env *env)
{
    t_queue     *head;
    t_queue     *tmp;
    t_link      *endlinks;

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
            tmp = head;
            head = head->next;
        }
        free(env->queue);
    }
    env->queue = NULL;
    env->end_queue = env->queue;
    return (1);
}

/*
***     CREATE QUEUE MAILLON AND APPEND IT
*/

void     append_queue(t_env *env, t_link *link, t_room *previous)
{
    t_queue *last;

    if (!(last = (t_queue*)malloc(sizeof(t_queue))))
        return ;
    last->room = link->dest;
    link->dest->inqueue = 1;
    link->dest->from = link;
    last->room->prev = previous;
    last->prev_flow = link->flow;
    link->dest->weight = link->flow == -1 ? previous->weight - 1 : previous->weight + 1;
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
***     DEPTH FIRST ON NEGATIVE FLOWS
*/

static void        depthfirst_queue(t_env *env, t_room *room)
{
    t_link  *link;

    link = room->linked_rooms;
    while (link)
    {
        if (link->flow == -1 && link->dest->inqueue != 1)
        {
            append_queue(env, link, room);
            link = link->dest->linked_rooms;
        }
        else
            link = link->next;
    }
}

/*
***     CHANGE SOURCE
*/

void        change_source(t_env *env, t_room *room, t_link *link, t_room *newprev)
{
    t_queue *queue;
    t_room  *prev;
    int     roomweight;
    int     prevweight;
    int     curweight;

    prev = room->prev;
    queue = env->queue;

    if (prev)
    {
        roomweight = link->flow == -1 ? newprev->weight - 1 : newprev->weight + 1;
        prevweight = room->from->rev->flow == -1 ? room->weight - 1 : room->weight + 1;
        room->prev = newprev;
        room->weight = roomweight;
        if (prevweight < prev->weight)
        {
            prev->prev = room;
            prev->weight = prevweight;
            prev->from = room->from->rev;
        }
        room->from = link;
    }
}

/*
***     GET LINKS TO ADD TO QUEUE
*/

void        get_queue(t_env *env, t_room *current)
{
    t_link  *current_link;

    int weight = 0;
    current->visited = 1;
    current->inqueue = 1;
    current_link = current->linked_rooms;
    // printf("\n QUEUE FROM %s\n", current->name);
    while (current_link)
    {
        weight = current_link->flow == -1 ? current->weight - 1 : current->weight + 1;
        if ((current_link->flow == -1 && current_link->dest->visited == 0
            && env->end_queue->prev_flow == 0))
        {
            append_queue(env, current_link, current);
            depthfirst_queue(env, current_link->dest);
            // printf("1 appending %s from %s, with %s having weight = %d\n", current_link->dest->name, current->name, current_link->dest->name, current_link->dest->weight);
            return ;
        }
        current_link = current_link->next;
    }
    current_link = current->linked_rooms;
    while (current_link)
    {
        weight = current_link->flow == -1 ? current->weight - 1 : current->weight + 1;
        if (current_link->dest->inqueue == 0 && current_link->flow != 1)
        {
            append_queue(env, current_link, current);
            // printf("2 appending %s from %s, with %s having weight = %d\n", current_link->dest->name, current->name, current_link->dest->name, current_link->dest->weight);
        }
        else if (current_link->dest->inqueue && current_link->dest->weight > weight)
        {
            // printf("%s might have a better prev : %s instead of %s\n", current_link->dest->name, current->name, current_link->dest->prev->name);
            change_source(env, current_link->dest, current_link, current);
        }
        current_link = current_link->next;
    }
}

/*
***     BFS
*/

int         bfs(t_env *env)
{
    t_room      *current;
    t_queue     *queue;

    current = env->start;
    if (initialize_bfs(env))
    {
        get_queue(env, current);
        if (!env->queue)
            return (0);
        current->visited = 1;
        queue = env->queue;
        current = queue->room;
        if (!ft_strcmp(current->name, env->end->name))
            return (1);
        while (ft_strcmp(current->name, env->end->name))
        {
            // printf("curname : %s\n", current->name);
            get_queue(env, current);
            // printf("after get queue\n");
            if (queue->next)
            {
                // printf("queue = queue->next : %s\n", queue->next->room->name);
                queue = queue->next;
            }
            else
                return (0);
            current = queue->room;
            if (!ft_strcmp(current->name, env->end->name))
            {
                // printf("bfs end 1\n");
                // printf("\n");
                // print_bfs(env);
                return (1);
            }
        }
    }
    // printf("bfs 0\n");
    return (0);
}
