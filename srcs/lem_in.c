/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:33 by epham             #+#    #+#             */
/*   Updated: 2019/07/29 13:19:48 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static	t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->line = NULL;
	env->ant_nb = 0;
	env->links = NULL;
	env->start = NULL;
	env->end = NULL;
	return (env);
}

int		main(int ac, char **av)
{
	t_env 	*env;

	if (!(env = init_env()))
		return (0);
	parse(env);
	return (0);
}
