/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:13:53 by epham             #+#    #+#             */
/*   Updated: 2019/07/08 12:20:25 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	elem = f(lst);
	if (!(new = ft_lstnew(elem->content, elem->content_size)))
		return (NULL);
	lst = lst->next;
	head = new;
	while (lst)
	{
		elem = f(lst);
		if (!(new->next = ft_lstnew(elem->content, elem->content_size)))
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
