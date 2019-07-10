/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:23:34 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:20:43 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if ((*(unsigned char*)s1) != (*(unsigned char*)s2))
			return ((*(unsigned char *)s1) - (*(unsigned char *)s2));
		s1++;
		s2++;
	}
	return (0);
}
