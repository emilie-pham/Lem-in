/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/10/14 15:11:56 by epham            ###   ########.fr       */
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
	print_map(env);
	if (edmond(env) != 0)
		print_sol(env, env->optimal_sol);
	free_table(env->table);
	free_links(env->links);
	free_lines(env->read);
	free_env(env);
	free(env);
	return (0);
}
