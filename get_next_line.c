/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:18:32 by ywake             #+#    #+#             */
/*   Updated: 2021/06/19 03:43:23 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	free_set(char **dst, char *src)
{
	free(*dst);
	*dst = src;
}

int	myabort(char *rdbuf, char **line, char **remain)
{
	free_set(&rdbuf, NULL);
	free_set(line, NULL);
	free_set(remain, NULL);
	return (-1);
}

int	ret(ssize_t rdrtn, char *rdbuf, char **line, char **remain)
{
	free_set(&rdbuf, NULL);
	if (rdrtn > 0)
		rdrtn = 1;
	if (*line == NULL || (*remain == NULL && rdrtn != 0))
		rdrtn = myabort(rdbuf, line, remain);
	return (rdrtn);
}

int	get_next_line(int fd, char **line)
{
	char		*rdbuf;
	static char	*remain[1];
	char		*ptr;
	ssize_t		rtn;

	if (set_ret_char(&rdbuf, malloc(BUFFER_SIZE + 1)) == NULL)
		return (myabort(rdbuf, NULL, NULL));
	*line = *remain;
	*remain = NULL;
	while (set_ret_long(&rtn, read(fd, rdbuf, BUFFER_SIZE)) >= 0)
	{
		rdbuf[rtn] = '\0';
		free_set(line, ft_strjoin(*line, (char *)rdbuf));
		if (*line != NULL && set_ret_char(&ptr, ft_strchr(*line, '\n')) != NULL)
		{
			*remain = ft_strndup(ptr + 1, -1);
			free_set(line, ft_strndup(*line, ptr - *line));
			return (ret(1, rdbuf, line, remain));
		}
		if (rtn == 0 || *line == NULL)
			return (ret(0, rdbuf, line, remain));
	}
	return (myabort(rdbuf, line, remain));
}
