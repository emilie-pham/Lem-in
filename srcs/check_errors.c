/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:15:35 by epham             #+#    #+#             */
/*   Updated: 2019/07/10 17:41:51 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		CHECK ANTS VALUE
*/

int		check_ants(t_env *env, char **value)
{
	int i;
	
	i = 0;
	while (value[0][i])
	{
		if (ft_isdigit(value[0][i]) == 0 && value[0][i] != '+')
			return (-1);
		i++;
	}
	env->ant_nb = ft_atol(value[0]);
	return (0);
}
