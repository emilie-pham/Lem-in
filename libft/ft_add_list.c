/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:23:41 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:24:38 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_add_list(t_list *list, char *str)
{
	t_list	*new;
	t_list	*begin;

	begin = list;
	if ((new = ft_create_list(str)) == NULL)
		return (NULL);
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		begin = new;
	return (begin);
}
