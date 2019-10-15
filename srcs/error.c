/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:46:02 by epham             #+#    #+#             */
/*   Updated: 2019/10/15 16:21:39 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		error_invalid_file(t_env *env)
{
	ft_strdel(&env->line);
	ft_putstr_fd("NOT A FILE\n", 2);
}

void		invalid_ants(t_env *env)
{
	ft_strdel(&env->line);
	ft_putstr_fd("INVALID NUMBER OF ANTS\n", 2);
}

void		room_problems(t_env *env, int i)
{
	ft_strdel(&env->line);
	free_lines(env->read);
	free_table(env->table);
	if (i == 1)
		ft_putstr_fd("LINK TO UNKNOWN ROOM\n", 2);
	else if (i == 2)
		ft_putstr_fd("ROOM END OR START ALREADY EXISTS\n", 2);
	else if (i == 3)
		ft_putstr_fd("DOUBLE ROOM\n", 2);
	else if (i == 4)
		ft_putstr_fd("ROOM START OR END MISSING\n", 2);
}

void		no_path(t_env *env)
{
	ft_strdel(&env->line);
	free_lines(env->read);
	free_table(env->table);
	free_queue(env);
	ft_putstr_fd("THERE IS NO PATH BETWEEN ROOM START AND END\n", 2);
}

void		link_to_itself(t_env *env)
{
	ft_strdel(&env->line);
	free_lines(env->read);
	free_table(env->table);
	ft_putstr_fd("ONE ROOM IS LINKED TO ITSELF\n", 2);
}
