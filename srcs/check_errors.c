/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:15:35 by epham             #+#    #+#             */
/*   Updated: 2019/07/11 11:33:17 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		CHECK ANTS VALUE
*/

int		check_ants(t_env *env, char **args)
{
	int i;
	
	i = 0;
	while (args[0][i])
	{
		if (ft_isdigit(args[0][i]) == 0 && args[0][i] != '+')
			return (-1);
		i++;
	}
	env->ant_nb = ft_atol(args[0]);
	return (0);
}

/*
***		GET START AND END
*/

int		get_start_end(t_env *env, char **args, char *startend)
{
	int i;
	char **room;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '#') != NULL && args[i][0] == '#')
		{
			if (args[i][1] == '#' && ft_strstr(args[i], startend) != NULL)
			{
				room = ft_strsplit(args[i + 1], ' ');
				if (ft_tablen(room) != 3)
					return (-1);
				if (ft_strdigit(room[1]) == 0 || ft_strdigit(room[2]) == 0)
					return (-1);
				env->start->name = room[0];
				env->start->coord_x = ft_atol(room[1]);
				env->start->coord_y = ft_atol(room[2]);
				
				if (ft_strcmp(startend, "start") == 0)
					printf("\n\nSTART NAME : %s\n\nX : %d\n\nY : %d\n\n", env->start->name, env->start->coord_x, env->start->coord_y);
				if (ft_strcmp(startend, "end") == 0)
					printf("\n\nEND NAME : %s\n\nX : %d\n\nY : %d\n\n", env->start->name, env->start->coord_x, env->start->coord_y);
				return (0);
			}
		}
		i++;
	}
	return (-1);
}
