/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/07/23 12:34:43 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
CAS ERREUR

- Pas de link sortant de start
*/


/*
***     CREATING PATH WITH START ROOM
*/

t_path      *start_path(t_room *start)
{
    t_path  *path;

    if (!start || start->linked_rooms == NULL)
        return (NULL);
    if (!(path = malloc(sizeof(t_path *))))
        return (NULL);
    path->room = start;
    path->next = NULL;
    return (path);
}

/*
***     BFS
*/

t_path      *bfs(t_env *env)
{
    t_path  *path;
    t_queue *queue;
    t_queue *tmp;
    t_room  *current;
    t_link  *links;

    if (!(queue = malloc(sizeof(t_queue *))))
        return (NULL);
    current = env->start;
    links = current->linked_rooms;
    env->start->prev = NULL;
    env->start->visited = 1;
    // adds all room attached to start to queue
    while (links->next != NULL)
    {
        links->dest->prev = current;
        if (links->flow != 1)
            add_to_queue(&queue, links->dest);
        links = links->next;
    }
    tmp = queue;
    current = queue->room;
    while (queue->next != NULL || current == env->end)
    {
        if (current == env->end)
            break;
        links = current->linked_rooms;
        while (links->next != NULL)
        {
            if (links->flow != 1)
            {
                if (links->dest->prev == NULL)
                    links->dest->prev = current;
                if (links->dest->visited != 1)
                    add_to_queue(&queue, links->dest);
            }
        }
    }
}