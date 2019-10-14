/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 08:26:15 by epham             #+#    #+#             */
/*   Updated: 2019/10/14 16:37:14 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void    *mem;
    if (!(mem = (void *)malloc(sizeof(void) * size)))
        return (NULL);
    ft_bzero(mem, size);
    return (mem);
}
