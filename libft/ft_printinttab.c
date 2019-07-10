/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printinttab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:02:51 by epham             #+#    #+#             */
/*   Updated: 2019/04/18 18:07:10 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printinttab(int **s, int len, int width)
{
	int i;
	int j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < width)
		{
			ft_putnbr(s[i][j++]);
			if (j < width)
				ft_putchar(' ');
		}
		ft_putchar('\n');
		i++;
	}
}
