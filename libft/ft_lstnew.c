/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:18:02 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:20:30 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->next = NULL;
	new->content_size = content ? content_size : 0;
	new->content = content ? ft_memalloc(content_size + 1) : NULL;
	if (content)
		ft_memcpy(new->content, content, content_size);
	return (new);
}
