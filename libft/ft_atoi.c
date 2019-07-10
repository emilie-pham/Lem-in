/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:31:54 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:18:01 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_atoi(const char *str)
{
	int		to_return;
	int		sign;
	char	*pointer;

	pointer = (char*)str;
	sign = 1;
	to_return = 0;
	while (((*pointer >= 9 && *pointer <= 13) || *pointer == 32))
		pointer++;
	if (*pointer == '-')
	{
		sign = -1;
		pointer++;
	}
	else if (*pointer == '+')
		pointer++;
	while (*pointer >= '0' && *pointer <= '9')
	{
		to_return = (to_return * 10) + (*pointer - 48);
		pointer++;
	}
	return (to_return * sign);
}
