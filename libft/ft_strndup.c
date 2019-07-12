/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:09:05 by yoribeir          #+#    #+#             */
/*   Updated: 2019/07/12 16:10:02 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *src, int n)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(src);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	while (src[i] && n)
	{
		ret[i] = src[i];
		n--;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
