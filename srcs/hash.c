/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:19:54 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/30 16:19:33 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long long hash_value(char *key)
{
	unsigned long long hashedvalue;

	hashedvalue = 0;
	while (*key)
	{
		hashedvalue = *key + 31 * hashedvalue;
		key++;
	}
	return (hashedvalue % TABLE_SIZE);
}

void	insert_hash_table(t_room **table, t_room *room)
{
	t_room	*newnode;
	t_room	*tmp;
	size_t	hashedvalue;

	hashedvalue = hash_value(room->name);
	// printf("room %s = %ld\n", room->name, hashedvalue);
	if (table[hashedvalue]->name == NULL)
		table[hashedvalue] = room;
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

void	init_table(t_room **table)
{
	int i = 0;

	while (i < TABLE_SIZE)
	{
		table[i] = malloc(sizeof(t_room));
		table[i]->name = NULL;
		i++;
	}
}
