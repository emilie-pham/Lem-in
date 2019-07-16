/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:56 by epham             #+#    #+#             */
/*   Updated: 2019/07/12 13:48:11 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		INITIALIZE THE ENV STRUCTURE
*/

t_env	*initialize_env(t_env **env)
{
	if (!(*env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	if (!((*env)->input = (char *)malloc(sizeof(char))))
		return (NULL);
	if (!((*env)->start = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	if (!((*env)->end = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	return (*env);
}

/*
***		INITIALIZE THE ROOM STRUCTURE
*/

t_room	*initialize_room(char *name, int x, int y)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(*room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->coord_x = x;
	room->coord_y = y;
	return (room);
}
