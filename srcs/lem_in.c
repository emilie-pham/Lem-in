/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/10/16 19:58:58 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				main(int ac, char **av)
{
	t_env	*env;

	if (!(env = init_env()))
		return (0);
	parse(env);
	print_map(env);
	if (edmond(env) != 0)
	{
		env->countsteps = env->steps;
		print_sol(env, env->optimal_sol);
	}
	if (ac == 2 && !ft_strcmp(av[1], "-c"))
		ft_printf("\nnumber of lines : %lu\n", env->countsteps);
	free_table(env->table);
	free_lines(env->read);
	free_env(env);
	free(env);
	return (0);
}
