/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/12 15:34:56 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void	ft_error(int error)
{
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
}

void	parse_ants(t_env *env)
{
	if (get_next_line(0, &env->line) < 1)
		ft_error(1);
	if (!ft_isdigit(*env->line))
		ft_error(1);
	env->ant_nb = ft_atoi(env->line);
	if (env->ant_nb <= 0)
		ft_error(1);
	printf("ants	%d\n", env->ant_nb);
	ft_strdel(&env->line);
}

void	print_split(char **tab)
{
	int		i = 0;
	int		y = 0;

	while (tab[i])
	{
		while (tab[i][y])
		{
			printf("%c", tab[i][y]);
			y++;
		}
		printf(" ");
		y = 0;
		i++;
	}
	i = 0;
}

void	parse(t_env *env)
{
	parse_ants(env);
	parse_rooms(env);
	// parse_links();
}