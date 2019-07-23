/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:19:54 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/23 15:57:54 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long long hash_value(char *key, int size)
{
	unsigned long long hashedvalue;

	hashedvalue = 0;
	while (*key)
	{
		hashedvalue = *key + 31 * hashedvalue;
		key++;
	}
	return (hashedvalue % size);
}

size_t		list_size(t_room *rooms)
{
	size_t		count;

	count = 0;
	while (rooms)
	{
		count++;
		rooms = rooms->next;
	}
	return (count);
}

void	print_hash(t_hash *table, size_t size)
{
	t_hash	*current;

	
}

t_hash	*create_hash_table(t_env *env)
{
	t_hash	*table;

	env->table_size = list_size(env->rooms);
	table = malloc(sizeof(t_hash) * env->table_size);
	fill_hash_table(env, table);
	table->next = NULL;
	return (table);
}

void	insert_hash_table(t_hash *table, t_room *current, size_t hashedvalue)
{
	t_hash	*tmp;

	if (table[hashedvalue].node == NULL)
		table[hashedvalue].node = current;
	else
	{
		tmp = &table[hashedvalue];
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next->node = current;
	}
}

t_hash	*fill_hash_table(t_env *env, t_hash *table)
{
	t_room	*current;
	size_t	hashedvalue;

	current = env->rooms;
	while (current)
	{
		hashedvalue = hash_value(current->name, env->table_size);
		insert_hash_table(table, current, hashedvalue);
		current = current->next;
	}
	return (table);
}

