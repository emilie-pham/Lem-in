/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 08:26:15 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:20:33 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *s;

	if (!(s = (char*)malloc(sizeof(char*) * size + 1)))
		return (NULL);
	ft_bzero(s, size);
	return (s);
}
