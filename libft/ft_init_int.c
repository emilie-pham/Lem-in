/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:17:16 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:18:54 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_init_int(int len)
{
	int i;
	int *tab;

	i = 0;
	if (len > 0)
	{
		if (!(tab = (int *)malloc(sizeof(int) * len)))
			return (NULL);
		while (i < len)
		{
			tab[i] = 0;
			i++;
		}
		return (tab);
	}
	return (NULL);
}
