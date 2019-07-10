/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:16:47 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:18:43 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_create_list(char *str)
{
	t_list	*list;

	list = NULL;
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->content = str;
	list->next = NULL;
	return (list);
}
