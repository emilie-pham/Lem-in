/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:59:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/12 14:15:37 by yoribeir         ###   ########.fr       */
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
	printf("nb ants %d\n", env->ant_nb);
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

t_room	*create_room(char *line)
{
	char	**split;
	t_room	*room;

	split = ft_strsplit(line, ' ');
	print_split(split);
	if (!(room = ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(split[0]);
	room->coord_x = ft_atoi(split[1]);
	room->coord_y = ft_atoi(split[2]);
	room->next = NULL;
	return (room);
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
	split = ft_strsplit(line, ' ');
	while (split[count])
		count++;
	if (count == 3)
	{
		if (is_room_name(split[0]) && ft_isdigit(split[1][0]))
			ret = 1;
	}
	return (ret);
}

void	add_room(t_env *env, t_room *room)
{
	t_room	*current;

	current = room;
	if (!env->rooms)
		env->rooms = room;
	else
	{
		while (current)
			current = current->next;
		current->next = room;
	}
}

void	print_list(t_room *head)
{
	t_room *current;

	current = head;
	while (current)
	{
		printf("room:%s %d %d\n", current->name, current->coord_x, current->coord_y);
		current = current->next;
	}
}

void	parse_rooms(t_env *env)
{
	env->rooms = NULL;
	while (get_next_line(0, &env->line) == 1)
	{
		if (is_room(env->line))
		{
			add_room(env, create_room(env->line));
			// create_room(env->line);
		}
	}
	print_list(env->rooms);
}


void	parse(t_env *env)
{
	parse_ants(env);
	parse_rooms(env);
	// parse_links();
}