/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/07/30 21:21:54 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***     INITIALIZE BFS : PREV TO NULL AND VISITED TO 0
*/

void        initialize_bfs(t_env *env)
{
    t_queue     *head;
    t_queue     *tmp;
    
    if (env->queue)
    {
        head = env->queue;
        while (head)
        {
            printf("queue\n");
            head->room->prev = NULL;
            head->room->visited = 0;
            tmp = head;
            head = head->next;
            free(tmp);
        }
        free(env->queue);
    }
    env->queue = NULL;
    env->end_queue = env->queue;
}

/*
***     CREATE QUEUE MAILLON AND APPEND IT
*/

void     append_queue(t_env *env, t_link *link, t_room *previous)
{
    t_queue *last;

    printf("Append %s to queue\n", link->dest->name);
    if (!(last = malloc(sizeof(t_queue*))))
        return ;
    last->room = link->dest;
    link->dest->inqueue = 1;
    last->room->prev = previous;
    last->prev_flow = link->flow;
    last->next = NULL;
    if (!env->queue)
    {
        env->queue = last;
        env->end_queue = env->queue;
        print_queue(env);
        return ;
    }
    env->end_queue->next = last;
    env->end_queue = env->end_queue->next;
    print_queue(env);
}

/*
***     GET LINKS TO ADD TO QUEUE
*/

void        get_queue(t_env *env, t_room *current)
{
    t_link  *current_link;

    current->visited = 1;
    current->inqueue = 1;
    current_link = current->linked_rooms;
    printf("\nCURRENT ROOM %s\n", current->name);
    while (current_link)
    {
        if ((current_link->flow == -1 && current_link->dest->visited == 0
            && env->end_queue->prev_flow == 0))
        {
            append_queue(env, current_link, current);
            return ;
        }
        current_link = current_link->next;
    }
    current_link = current->linked_rooms;
    while (current_link)
    {
        if (current_link->dest->inqueue == 0 && current_link->flow != 1)
        {
            append_queue(env, current_link, current_link->dest);
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
    initialize_bfs(env);
    get_queue(env, current);
    if (!env->queue)
    {
        printf("NO QUEUE\n");
        return (0);
    }
    current->visited = 1;
    queue = env->queue;
    current = queue->room;
    while (current != env->end)
    {
        get_queue(env, current);
        queue = queue->next;
        current = queue->room;
        printf("\nNext room to check the queue : %s\n", current->name);
    }
    if (current == env->end)
        return (1);
    else
        return (0);
}
