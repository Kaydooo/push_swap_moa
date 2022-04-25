/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 07:27:18 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/25 11:41:48 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

char	*ft_line(char	**s, int i)
{
	char	*temp;
	char	*ret;

	if (ft_strchr(*s, '\n'))
	{
		temp = *s;
		ret = ft_substr(*s, 0, i);
		*s = ft_strdup(temp + i);
		free(temp);
		temp = NULL;
		return (ret);
	}
	else if (*s)
	{
		temp = ft_strdup(*s);
		ft_free(s);
		return (temp);
	}
	return (NULL);
}

int	nl_index(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int	ft_reader(char **save, int fd, int n)
{
	char	*temp;
	char	buff[BUFFER_SIZE + 1];

	while (n && !ft_strchr(*save, '\n'))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buff[n] = '\0';
		temp = *save;
		*save = ft_strjoin(temp, buff);
		free(temp);
	}
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*save;
	int			index;
	int			b;

	b = 1;
	if (fd < 0 || fd > 8192 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	b = ft_reader(&save, fd, b);
	if (*save == '\0' && b <= 0)
	{
		ft_free(&save);
		return (NULL);
	}
	index = nl_index(save);
	return (ft_line(&save, index + 1));
}
