/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/11 12:16:15 by epham            ###   ########.fr       */
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
***		-1 : INVALID ANT NB
***		-2 : NO START OR END
***		-3 : EMPTY LINES
*/
	#include <stdio.h>

int			check_input(t_env *env)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_strsplit(env->input, '\n');
	printf("ARGLEN = %zu\n\n", ft_tablen(args));
	printf("WORDNB = %d\n\n", ft_count_words(env->input, '\n'));
	if (check_ants(env, args) == -1)
		return (-1);
	if (get_start_end(env, args, "start") == -1 || get_start_end(env, args, "end") == -1)
		return (-2);
	while (args[i])
	{
		printf("LINE : %s\n", args[i]);
		if (ft_strlen(args[i]) == 0)
			return (-3);
		i++;
	}
	// checker les rooms
	// checker les links
	return (0);
}
