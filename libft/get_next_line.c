/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:38:10 by yoribeir          #+#    #+#             */
/*   Updated: 2019/10/11 16:23:34 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_fd(t_list **head, int fd)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(head, tmp);
	return (tmp);
}

char	*read_line(t_list *list, char *buffer, int sz)
{
	char	*tmp;
	char	*ret;

	buffer[sz] = '\0';
	tmp = list->content;
	ret = ft_strjoin(list->content, buffer);
	free(tmp);
	return (ret);
}

char	*save_rest(t_list *list, int sz)
{
	char *tmp;
	char *ret;

	tmp = list->content;
	ret = ft_strdup(list->content + sz);
	free(tmp);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	int				readsz;
	char			buffer[BUFF_SIZE + 1];
	static	char	*str;
	char			*tmp;

	if (fd < 0 || !line || read(fd, buffer, 0) < 0)
		return (-1);
	if (!str)
		str = ft_strdup("");
	while ((readsz = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[readsz] = '\0';
		tmp = str;
		str = ft_strjoin(str, buffer);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	readsz = 0;
	while (str[readsz] != '\n' && str[readsz])
		readsz++;
	*line = ft_strndup(str, readsz);
	if (str[readsz] == '\n')
		readsz++;
	tmp = str;
	str = ft_strdup(str + readsz);
	free(tmp);
	return (readsz > 0 ? 1 : 0);
}
