/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:49:01 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:21:34 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst(t_list *list)
{
	while (list)
	{
		if (list->content)
			ft_putstr(list->content);
		list = list->next;
	}
}
