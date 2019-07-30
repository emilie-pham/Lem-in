/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:06:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/30 15:02:02 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_rooms(t_room *head)
{
	t_room *current;

	current = head;
	while (current)
	{
		printf("room	%s %d %d\n", current->name, current->coord_x, current->coord_y);
		current = current->next;
	}
}

void	print_split(char **tab)
{
	int		i = 0;
	int		y = 0;

	while (tab[i])
	{
		while (tab[i][y])
		{
			printf("%c", tab[i][y]);
			y++;
		}
		printf(" ");
		y = 0;
		i++;
	}
	i = 0;
}

void	print_linked(t_room *room)
{
	t_room *current;

	current = room;
	if (current)
		printf("linked rooms ");
	while (current)
	{
		printf("[%s]", current->name);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("\n");
}

void	print_hash(t_room **table, size_t size)
{
	t_room	*collisions;
	size_t i;

	i = 0;
	while (i < size)
	{
		if (table[i]->name)
		{
			printf("hash %s : ", table[i]->name);
			print_linked(collisions);
			collisions = table[i];
			while (collisions->next)
			{
				collisions = collisions->next;
				printf(" -> %s", collisions->name);
			}
		}
		if (table[i]->name)
			printf("\n");
		i++;
	}
}

void	ft_error(int error)
{
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
}
