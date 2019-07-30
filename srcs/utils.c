/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:06:14 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/29 16:09:33 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_links(t_link *head)
{
	t_link *current;

	current = head;
	while (current)
	{
		printf("link	 %s-%s\n", current->from->name, current->dest->name);
		current = current->next;
	}
}

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

void	print_hash(t_room **table, size_t size)
{
	t_room	*collisions;
	size_t i;

	i = 0;
	while (i < size)
	{
		if (table[i]->name)
		{
			printf("hash %s", table[i]->name);
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
