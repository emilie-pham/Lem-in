/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:00:49 by anradix           #+#    #+#             */
/*   Updated: 2019/07/11 11:47:03 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsplit(char const *s, char c)
{
	char				**tab;
	unsigned int		j;
	unsigned int		k;

	j = 0;
	if (!s || !(tab = malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			k = 0;
			if (!(tab[j] = (char*)malloc(sizeof(char) * ft_word_len(s, c) + 1)))
				return (NULL);
			while (*s != c && *s != '\0')
				tab[j][k++] = *s++;
			tab[j][k] = '\0';
			j++;
		}
		else
			s++;
	}
	tab[j] = NULL;
	return (tab);
}
