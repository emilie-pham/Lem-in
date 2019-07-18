/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anradixt <anradix@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 11:57:31 by epham             #+#    #+#             */
/*   Updated: 2019/07/18 18:33:29 by anradixt         ###   ########.fr       */
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
    t_path  path;

    if (start->linked_rooms == NULL)
        return (NULL);
    if (!(path = malloc(sizeof(t_path))))
        return (NULL);
    path->room = start;
    path->link = NULL;
    path->prev = NULL;
    path->next = NULL;
    return (path);
}

/*
***     CHECKS THAT ROOM IS NOT ALREADY IN PATH
*/

t_path         check_pathroom(t_room *room, t_path *path)
{
    t_room *head;

    head = path;
    while (path->next == NULL)
    {
        if (path->room == room)
        {
            remove_path(head);
            return (NULL);
        }
        path = path->next;
    }
    return (head);
}

/*
***     CREATE PATHNODE WITH NEW ROOM
*/

t_path      *create_pathroom(t_room *room, t_link *link)
{
    t_path  pathroom;

    if (!(pathroom = malloc(sizeof(t_path))))
        return (NULL);
    pathroom->room = room;
    pathroom->link = link;
    pathroom->next = NULL;
    return (pathroom);
}

/*
***     ADD PATH NODE TO PATH
*/

t_path      *append_node(t_path *path, t_path *newroom)
{
    t_path  *head;
    t_path  *prev;

    head = path;
    while (path->next != NULL)
    {
        if (path->next->next == NULL)
            prev = path;
        path = path->next;
    }
    path = newroom;
    path->prev = prev;
    return (head);
}

/*
***     DELETING INVALID PATH
*/

void        remove_path(t_path *head)
{
    t_path  *tmp;
    while (head->next != NULL)
    {
        tmp = head->next;
        head = NULL;
        head = tmp;
    }
}
