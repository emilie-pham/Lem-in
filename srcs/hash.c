/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:19:54 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/23 14:34:21 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long long hash_value(char *key, int size)
{
	unsigned long long hashedvalue;

	hashedvalue = 0;
	while (*key)
	{
		hashedvalue = *key + 42 * hashedvalue;
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

void	print_hash(t_hash *table)
{
	t_hash	*current;

	current = table;
	while (current)
	{
		// printf("%s\n", );
		current = current->next;
	}
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

t_hash	*fill_hash_table(t_env *env, t_hash *table)
{
	t_room	*current;
	size_t	hashedvalue;

	current = env->rooms;
	while (current)
	{
		hashedvalue = hash_value(current->name, env->table_size);
		table[hashedvalue].node = current;
		table->node = current;
		current = current->next;
	}
	return (table);
}

