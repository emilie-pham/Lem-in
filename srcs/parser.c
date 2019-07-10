/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/10 17:43:38 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
***		READ AND SAVE INPUT INTO STRUCTURE
*/

void		get_input(t_env *env)
{
	char	*line;
	char	*tmp;
	
	while (get_next_line(0, &line) == 1)
	{
		tmp = env->input;
		env->input = ft_strjoin(env->input, line);
		free(tmp);
		ft_strdel(&line);
	}
}

/*
***		CHECK IF INPUT IS VALID
*/
	#include <stdio.h>

int			check_input(t_env *env)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_strsplit(env->input, '\n');
	if (check_ants(env, args) == -1)
		return (-1);
	// checker les rooms
	// checker les links
	return (0);
}
