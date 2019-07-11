/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:15:35 by epham             #+#    #+#             */
/*   Updated: 2019/07/11 14:25:22 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		CHECK ANTS VALUE
*/

int		check_ants(t_env *env, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != '+')
			return (-1);
		i++;
	}
	env->ant_nb = ft_atol(line);
	return (0);
}

/*
***		COMMENT LINE OR START/END OR EMPTY LINE
***		0 : NOT A COMMENT
***		1 : COMMENT
***		2 : START/END
***		-1 : EMPTY STRING
*/

int		is_comment(t_env *env, char *line, char *startend)
{
	int i;

	if (line[0] == '#')
	{
		if (line[1] == '#' && ft_strstr(line, startend) != NULL)
			return (2);
		return (1);
	}
	if (ft_strlen(line) == 0)
		return (-1);
	return (0);
}

/*
***		GET START OR END
*/

int		get_start_end(t_env *env, char *line, char *startend)
{
	int		i;
	char	**room;

	room = ft_strsplit(line, ' ');
	if (ft_tablen(room) != 3)
		return (-1);
	if (ft_strdigit(room[1]) == 0 || ft_strdigit(room[2]) == 0)
		return (-1);
	if (ft_strcmp(startend, "start") == 0)
	{
		env->start->name = room[0];
		env->start->coord_x = ft_atoi(room[1]);
		env->start->coord_y = ft_atoi(room[2]);
	}
	else if (ft_strcmp(startend, "end") == 0)
	{
		env->end->name = room[0];
		env->end->coord_x = ft_atoi(room[1]);
		env->end->coord_y = ft_atoi(room[2]);
	}
	return (0);
}
