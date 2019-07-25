/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:19:54 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/23 20:02:58 by yoribeir         ###   ########.fr       */
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

void	_print_hash(t_hash *table, size_t size)
{
	t_room	*collisions;
	size_t i;

	i = 0;
	while (i < size)
	{
		if (table[i].node)
		{
			printf("room hash %s", table[i].node->name);
			collisions = table[i].node;
			while (collisions->next)
			{
				collisions = collisions->next;
				printf("+ %s\n", collisions->name);
			}
		}
		printf("\n");
		i++;
	}
}

// void	print_hash(t_hash *table, size_t size)
// {
// 	t_hash	*collisions;
// 	size_t	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		if (table[i].node)
// 		{
// 			printf("hash	%s", table[i].node->name);
// 			collisions = &table[i];
// 			while (collisions->next)
// 			{
// 				collisions = collisions->next;
// 				printf(" -> %s", collisions->node->name);
// 			}
// 		}
// 		if (table[i].node)
// 			printf("\n");
// 		i++;
// 	}
// }

// t_hash	*create_hash_table(t_env *env)
// {
// 	t_hash	*table;

// 	env->table_size = list_size(env->rooms);
// 	printf("table size %zu\n", env->table_size);
// 	table = ft_memalloc(sizeof(t_hash) * env->table_size);
// 	fill_hash_table(env, table);
// 	// print_hash(table, env->table_size);
// 	table->next = NULL;
// 	return (table);
// }

void	insert_hash_table(t_room *table, t_room *room, size_t hashedvalue)
{
	t_room	*newnode;
	t_room	*tmp;

	if (table[hashedvalue].name == NULL)
		table[hashedvalue] = *room;
	else
	{
		newnode = ft_memalloc(sizeof(t_room));
		newnode = room;
		tmp = &table[hashedvalue];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

void	fill_hash_table(t_env *env, t_room *table, t_room *room)
{
	size_t	hashedvalue;

	hashedvalue = hash_value(room->name);
	insert_hash_table(table, room, hashedvalue);
}

void	init_table(t_room *table)
{
	int i = 0;

	while (i < TABLE_SIZE)
	{
		table[i] = malloc(sizeof(t_room));
		table[i].name = NULL;
		i++;
	}
}

// t_hash	*fill_hash_table(t_env *env, t_hash *table)
// {
// 	t_room	*current;
// 	size_t	hashedvalue;

// 	current = env->rooms;
// 	while (current)
// 	{
// 		hashedvalue = hash_value(current->name, env->table_size);
// 		// printf("%s = %zu\n", current->name, hashedvalue);
// 		insert_hash_table(table, current, hashedvalue);
// 		current = current->next;
// 	}
// 	return (table);
// }

