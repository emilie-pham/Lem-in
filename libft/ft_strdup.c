/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:18:43 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:22:22 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;

	if (!(dup = (char*)malloc(sizeof(*s) * (ft_strlen(s) + 1))))
		return (NULL);
	return (ft_strcpy(dup, s));
}
