/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:10:46 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/14 17:40:58 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_link(t_link *link)
{
	ft_printf("\ndest : %s\n", link->dest->name);
	ft_printf("flow : %d\n", link->flow);
	ft_printf("from : %s\n\n", link->rev->dest->name);
}

void	print_links(t_room *room)
{
	t_link *head;

	head = room->linked_rooms;
	ft_printf("room %s is connected to : ", room->name);
	while (head)
	{
		if (head->next)
			ft_printf("room %s, ", head->dest->name);
		else
			ft_printf("room %s", head->dest->name);
		head = head->next;
	}
}

void	print_hash(t_room **table, size_t size)
{
	t_room	*collisions;
	size_t i;
	int	count = 0;

	i = 0;
	while (i < size)
	{
		if (table[i])
		{
			ft_printf("hash [%s] ", table[i]->name);
			print_links(table[i]);
			collisions = table[i];
			while (collisions->next)
			{
				count++;
				collisions = collisions->next;
				ft_printf(" -> %s", collisions->name);
			}
			count++;
		}
		if (table[i])
			ft_printf("\n");
		i++;
	}
	ft_printf("room number %d\n", count);
}

void	print_path(t_path *head)
{
	t_path *current;

	if (head)
	{
		current = head;
		while (current)
		{
			ft_printf("%s | ", current->room->name);
			current = current->next;
		}
		ft_printf("\n");
	}
}

void	print_paths(t_sol *current_sol)
{
	t_sol	*head;
	t_path		*start;

	head = current_sol;
	ft_printf("SOLUTION SET :\n");
	while (current_sol)
	{
		ft_printf("PATHLEN : %d\n", current_sol->pathlen);
		ft_printf("ANTS TO SEND IN THIS PATH : %d\n", current_sol->ants);
		start = current_sol->path;
		while (current_sol->path)
		{
			ft_printf("%s | ", current_sol->path->room->name);
			current_sol->path = current_sol->path->next;
		}
		current_sol->path = start;
		ft_printf("\n\n");
		current_sol = current_sol->next;
	}
	current_sol = head;
}

void	print_queue(t_env *env)
{
	t_queue *queue;

	// ft_printf("START ROOM : %s, END ROOM : %s\n", env->start->name, env->end->name);
	if (env->queue)
	{
		queue = env->queue;
		ft_printf("\nQUEUE : ");
		while (queue->next)
		{
			ft_printf("room %s || ", queue->room->name);
			queue = queue->next;
		}
		ft_printf("room %s\n\n", queue->room->name);
	}
}

void	print_bfs(t_env *env)
{
	t_room *cur;

	cur = env->end;
	while (cur && ft_strcmp(cur->name, env->start->name))
	{
		ft_printf(" %s w=%d <-", cur->name, cur->weight);
		cur = cur->prev;
	}
	ft_printf("\n\n");
}

/*
***		FREE PATH
*/

void	free_path(t_path *path)
{
	t_path *tmp;

	while (path)
	{
		tmp = path;
		path->room = NULL;
		path = path->next;
		tmp->next = NULL;
		free(tmp);
	}
}

/*
***		FREE SOL
*/

void	free_sol(t_sol *sol)
{
	t_sol *tmp;

	if (sol)
	{
		while (sol)
		{
			free_path(sol->path);
			tmp = sol;
			sol = sol->next;
			tmp->next = NULL;
			free(tmp);
		}
	}
}

void	free_links(t_link *links)
{
	t_link	*tmp;
	t_link	*tmp1;

	tmp = links;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}

void 	free_2darray(char **arr)
{
	int y;

	y = 0;
	while (arr[y])
	{
		ft_strdel(&arr[y]);
		y++;
	}
	free(arr);
}

void	ft_error(int error)
{
	if (error == 1)
		ft_putstr_fd("ERROR\n", 2);
	if (error == 2)
		ft_putstr_fd("LINK TO UNKNOWN ROOM\n", 2);
	if (error == 3)
		ft_putstr_fd("INVALID ANTS\n", 2);
	if (error == 4)
		ft_putstr_fd("ROOM START OR END MISSING\n", 2);
	if (error == 5)
		ft_putstr_fd("NO PATH FROM START TO END\n", 2);
	if (error == 6)
		ft_putstr_fd("ROOM END OR START ALREADY EXISTS\n", 2);
	if (error == 7)
		ft_putstr_fd("MALLOC FAILED\n", 2);
	if (error == 8)
		ft_putstr_fd("DOUBLE ROOM\n", 2);
	if (error == 9)
		ft_putstr_fd("ROOM LINKED TO ITSELF\n", 2);
	exit(1);
}

void	free_queue(t_env *env)
{
	t_queue	*head;
	t_queue	*tmp;

	if (env->queue)
	{
		head = env->queue;
		while (head)
		{
			head->room->prev = NULL;
			head->room->visited = 0;
			head->room->inqueue = 0;
			head->room->weight = 0;
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
	env->queue = NULL;
	env->end_queue = NULL;
}

void	free_env(t_env *env)
{
	ft_strdel(&env->line);
	// if (env->read)
		// free_lines(env->read);
	// if (env->table)
		// free_table(env->table);
	if (env->queue)
		free_queue(env);
	// if (env->current_sol)
		// free_sol(env->current_sol);
		// ft_printf("ENV CURRSOL\n");
	// if (env->optimal_sol)
		// free_sol(env->current_sol);
		// ft_printf("ENV OPTIMALSOL\n");
}
