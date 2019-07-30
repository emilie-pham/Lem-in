/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/29 16:11:28 by anonymous        ###   ########.fr       */
=======
/*   Updated: 2019/07/29 19:10:02 by epham            ###   ########.fr       */
>>>>>>> 38debf39d9083b0986dd396db76cee3227c57659
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	parse_ants(t_env *env)
{
	if (get_next_line(0, &env->line) < 1)
		ft_error(1);
	if (!ft_isdigit(*env->line))
		ft_error(1);
	env->ant_nb = ft_atoi(env->line);
	if (env->ant_nb <= 0)
		ft_error(1);
	printf("ants	%d\n", env->ant_nb);
	ft_strdel(&env->line);
}

void	parse(t_env *env)
{
	env->links = NULL;
	t_room	*room;
	t_room	*table[TABLE_SIZE];

	init_table(table);
	parse_ants(env);
	while (get_next_line(0, &env->line) == 1)
	{
		if (is_room(env->line))
		{
			// printf("ROOM %s\n", env->line);
			room = create_room(env->line);
			insert_hash_table(table, room);
		}
		if (is_link(env->line))
		{
<<<<<<< HEAD
			// printf("LINK %s\n", env->line);
			add_link(env, get_link(env, table, env->line));
=======
			printf("LINK %s\n", env->line);
			get_link(env, table, env->line);
>>>>>>> 38debf39d9083b0986dd396db76cee3227c57659
		}
		if (is_command(env->line))
		{
			// printf("COMMAND %s\n", env->line);
			parse_startend(env, table);
		}
		// if (is_comment(env->line))
			// printf("comment %s\n", env->line);
		if (!is_room(env->line) && !is_link(env->line) && !is_comment(env->line)
			&& !is_command(env->line))
		{
			printf("BREAK\n");
			break ;
		}
	}
<<<<<<< HEAD
	// printf("READ\n");
=======
	printf("READ\n");
>>>>>>> 38debf39d9083b0986dd396db76cee3227c57659
	// print_links(env->links);
	print_hash(table, TABLE_SIZE);
}
