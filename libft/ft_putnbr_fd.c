/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:03:44 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:21:37 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long x;

	x = (long long)n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x = -x;
	}
	if (x >= 10)
		ft_putnbr_fd(x / 10, fd);
	ft_putchar_fd((x % 10) + '0', fd);
}
