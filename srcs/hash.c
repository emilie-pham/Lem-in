/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:11:33 by yoribeir          #+#    #+#             */
/*   Updated: 2019/08/05 14:14:23 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void				insert_hash_table(t_room **table, t_room *room)
{
	t_room	*newnode;
	t_room	*tmp;
	size_t	hashedvalue;

	hashedvalue = hash_value(room->name);
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

void				init_table(t_room **table)
{
	int i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		table[i] = malloc(sizeof(t_room));
		table[i]->name = NULL;
		i++;
	}
}
