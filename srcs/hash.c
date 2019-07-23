/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:19:54 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/23 18:07:37 by yoribeir         ###   ########.fr       */
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
	size_t i;

	i = 0;
	while (i < size)
	{
		if (table[i].node)
			printf("room hash %s\n", table[i].node->name);
		i++;
	}
}

t_hash	*create_hash_table(t_env *env)
{
	t_hash	*table;

	env->table_size = list_size(env->rooms);
	printf("table size %zu\n", env->table_size);
	table = malloc(sizeof(t_hash) * env->table_size);
	fill_hash_table(env, table);
	print_hash(table, env->table_size);
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
			tmp = tmp->next;
		tmp->node = current;
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
		printf("%s = %zu\n", current->name, hashedvalue);
		insert_hash_table(table, current, hashedvalue);
		current = current->next;
	}
	return (table);
}

