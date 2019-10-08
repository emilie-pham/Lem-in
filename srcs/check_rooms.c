/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:20:02 by epham             #+#    #+#             */
/*   Updated: 2019/10/07 19:21:20 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	ft_tabdel(split);
	return (ret);
}
