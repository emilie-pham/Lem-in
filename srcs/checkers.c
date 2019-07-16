/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:44:50 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/16 18:15:37 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


int		is_command(char *line)
{
	if (line && ft_strlen(line) >= 2)
		if (!ft_strncmp(line, "##", 2))
			return (1);
	return (0);
}

int		is_comment(char *line)
{
	if (line && ft_strlen(line))
		if (!is_command(line) && !ft_strncmp(line, "#", 1))
			return (1);
	return (0);
}

int		is_link(char *line)
{
	if (line && ft_strlen(line) >= 3)
	{
		if (!is_comment(line) && !is_command(line) && !is_room(line))
			return (1);
		return (0);
	}
	return (0);
}

int		is_room_name(char *line)
{
	if (line && ft_strlen(line))
	{
		if (line[0] == 'L' || line[0] == '#')
			return (0);
	}
	return (1);
}

int		is_room(char *line)
{
	char	**split;
	int		count;
	int		ret;

	count = 0;
	ret = 0;
	if (!(split = ft_strsplit(line, ' ')))
		return (ret);
	while (split[count])
		count++;
	if (count == 3)
	{
		if (is_room_name(split[0]) && ft_strdigit(split[1]) &&
			ft_strdigit(split[2]))
			ret = 1;
	}
	return (ret);
}