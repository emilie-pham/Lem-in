/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:44:50 by anonymous         #+#    #+#             */
/*   Updated: 2019/07/16 13:24:12 by yoribeir         ###   ########.fr       */
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
