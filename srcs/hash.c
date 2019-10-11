/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:11:33 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/11 17:16:06 by yoribeir         ###   ########.fr       */
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
			if (table[i]->linked_rooms)
				free_links(table[i]->linked_rooms);
			free_rooms(table[i]);
		}
		i++;
	}
	free(table);
}
