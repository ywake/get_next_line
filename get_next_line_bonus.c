/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:18:32 by ywake             #+#    #+#             */
/*   Updated: 2020/07/08 14:38:08 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#	define FD_MAX 2560

void	free_set(char **dst, char *src)
{
	free(*dst);
	*dst = src;
}

int		myabort(char *rdbuf, char **line, char **remain)
{
	free_set(&rdbuf, NULL);
	free_set(line, NULL);
	free_set(remain, NULL);
	return (-1);
}

int		ret(ssize_t rdrtn, char *rdbuf, char **line, char **remain)
{
	free_set(&rdbuf, NULL);
	if (rdrtn > 0)
		rdrtn = 1;
	if (*line == NULL || (remain == NULL && rdrtn != 0))
		rdrtn = myabort(rdbuf, line, remain);
	return (rdrtn);
}

int		get_next_line(int fd, char **line)
{
	char		*rdbuf;
	static char	*remain[FD_MAX + 1];
	char		*ptr;
	ssize_t		rtn;

	if ((rdbuf = (char *)malloc(BUFFER_SIZE + 1)) == NULL)
		return (myabort(rdbuf, NULL, NULL));
	*line = remain[fd];
	remain[fd] = NULL;
	while ((rtn = read(fd, rdbuf, BUFFER_SIZE)) >= 0)
	{
		rdbuf[rtn] = '\0';
		free_set(line, ft_strjoin(*line, (char *)rdbuf));
		if ((ptr = ft_strchr(*line, '\n')) != NULL && *line != NULL)
		{
			remain[fd] = ft_strndup(ptr + 1, -1);
			free_set(line, ft_strndup(*line, ptr - *line));
			return (ret(1, rdbuf, line, &remain[fd]));
		}
		if (rtn == 0 || *line == NULL)
			return (ret(0, rdbuf, line, &remain[fd]));
	}
	return (myabort(rdbuf, line, &remain[fd]));
}
