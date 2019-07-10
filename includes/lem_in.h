/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/07/10 14:20:48 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_room
{
	char		*name;
	int			coord_x;
	int			coord_y;
}				t_room;

typedef struct	s_env
{
	int			ant_nb;
}				t_env;

#endif
