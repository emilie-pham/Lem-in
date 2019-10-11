/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/10/11 18:28:03 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				main(int ac, char **av)
{
	t_env	*env;

	(void)ac;
	(void)av;
	if (!(env = init_env()))
		return (0);
	parse(env);
	print_hash(env->table, TABLE_SIZE);
	// print_map(env);
	// if (edmond(env) != 0)
		// print_sol(env, env->optimal_sol);
	// print_paths(env->optimal_sol);
	free_table(env->table);
	free_lines(env->read);
	free(env);
	return (0);
}
