/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:05:58 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:20:54 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = src;
	d = dst;
	if (d == s)
		return (dst);
	if (s < d)
		ft_memcpy(d, s, len);
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
