/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/07/11 13:51:47 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		main(int ac, char **av)
{
	t_env *env;

	initialize_env(&env);

	parse(env);
	// get_input(env);
	// IF input is OK
	// if (check_input(env) == 0)
		// ft_putstr(env->input);
	// else
		// ft_putendl("ERROR");
	free(env->input);
	free(env);
	return (0);
}
