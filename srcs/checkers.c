/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:44:50 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/23 19:03:51 by yoribeir         ###   ########.fr       */
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

int		command_type(char *line)
{
	if (!ft_strcmp("##start", line))
		return (1);
	if (!ft_strcmp("##end", line))
		return (2);
	return (0);
}

int		is_comment(char *line)
{
	if (line && ft_strlen(line))
		if (!is_command(line) && !ft_strncmp(line, "#", 1))
			return (1);
	return (0);
}

int		count_letter(char *line, char letter)
{
	int		count;

	count = 0;
	while (*line)
	{
			if (*line == letter)
				count++;
			line++;
	}
	return (count);
}

int		is_link(char *line)
{
	char	**split;
	int		count;
	int		ret;

	count = 0;
	ret = 0;
	if (!(split = ft_strsplit(line, '-')))
		return (0);
	while (split[count])
		count++;
	if (count == 2)
	{
		if (!ft_strcmp(split[0], split[1]))
			return (0);
		if (count_letter(line, '-') > 1)
			return (0);
		return (1);
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