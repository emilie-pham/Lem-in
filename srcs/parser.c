/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/16 13:10:33 by yoribeir         ###   ########.fr       */
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
***		COMMENT LINE OR START/END OR EMPTY LINE
***		0 : REGULAR COMMENT
***		1 : START
***		2 : END
*/

int		comment_type(t_env *env, char *line)
{
	if (line[1] == '#' && ft_strstr(line, "start") != NULL)
	{
		printf("START\n");
		return (1);
	}
	if (line[1] == '#' && ft_strstr(line, "end") != NULL)
	{
		printf("END\n");
		return (2);
	}
	printf("COMMENT\n");
	return (0);
}

/*
***		GET TYPE OF LINE
***		-1 : EMPTY, 0 : COMMENT, 1 : START, 2 : END, 3 : ROOM, 4 : LINK
*/

int		get_data_type(t_env *env, char *line)
{
	char	**room;
	char	**links;
	int		ret;

	ret = 0;
	room = ft_strsplit(line, ' ');
	links = ft_strsplit(line, '-');
	if (ft_strlen(line) == 0)
		ret = -1;
	else if (line[0] == '#')
		ret = comment_type(env, line);
	else if (ft_tablen(room) == 3)
		ret = 3;
	else if (ft_tablen(links) == 2)
		ret = 4;
	ft_tabdel(room);
	ft_tabdel(links);
	return (ret);
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
	parse_links(env);
}