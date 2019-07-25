/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/07/25 17:57:10 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***     INITIALIZE BFS : PREV TO NULL AND VISITED TO 0
*/

void        initialize_bfs(t_env *env)
{
    t_queue  *head;
    
    head = env->queue;
    if (env->queue)
    {
        while (head)
        {
            head->room->prev = NULL;
            head->room->visited = 0;
            head = head->next;
        }
    }
}

/*
***     CREATE QUEUE MAILLON
*/

t_queue     *create_queue(t_link *link)
{
    t_queue *queue;

    if (!(queue = malloc(sizeof(t_queue*))))
        return (NULL);
    queue->room = link->dest;
    queue->next = NULL;
    return (queue);
}

/*
***     GET LINKS TO ADD TO QUEUE
*/

void        get_queue(t_env *env, t_room *current)
{
    t_link  *current_link;
    t_queue *last;

    current_link = current->linked_rooms;
    while (current_link)
    {
        if (current_link->flow == -1 && current_link->dest->visited == 0)
            break;
        current_link = current_link->next;
    }
    if (current_link->next == NULL)
    {
        current_link = current->linked_rooms;
        while (current_link)
        {
            if (current_link->dest->visited == 0 && current_link->flow != 1)
            {
                last = create_queue(current_link);
                env->end_queue->next = last;
                env->end_queue = last;
            }
            current_link = current_link->next;
        }
    }
}

/*
***     BFS
*/

int         bfs(t_env *env)
{
    initialize_bfs(env);
}
