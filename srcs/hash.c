/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:11:33 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/11 19:00:58 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		COMPUTE HASH VALUE (INDEX) OF ROOM
*/

unsigned long long	hash_value(char *key)
{
	unsigned long long	hashedvalue;

	hashedvalue = 0;
	while (*key)
	{
		hashedvalue = *key + 31 * hashedvalue;
		key++;
	}
	return (hashedvalue % TABLE_SIZE);
}

/*
***		INSERT ROOM IN HASH TABLE
*/

void				insert_hash_table(t_room **table, t_room *room)
{
	t_room *newnode;
	t_room *tmp;
	size_t hashedvalue;

	if (find_room(table, room->name))
		ft_error(8);
	hashedvalue = hash_value(room->name);
	if (table[hashedvalue] == NULL)
	{
		table[hashedvalue] = malloc(sizeof(t_room));
		table[hashedvalue] = room;
	}
	else
	{
		newnode = ft_memalloc(sizeof(t_room));
		newnode = room;
		tmp = table[hashedvalue];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

/*
***		FREE HASH TABLE
*/

void				free_table(t_room **table)
{
	int i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (table[i])
		{
			free_rooms(table[i]);
		}
		i++;
	}
	free(table);
}

void 			free_rooms(t_room *rooms)
{
	t_room *tmp;
	t_room *tmp1;

	tmp = rooms;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		if (tmp1->linked_rooms)
			free_links(tmp1->linked_rooms);
		free(tmp1->name);
		free(tmp1);
		tmp1 = NULL;
	}
}
