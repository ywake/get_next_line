/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:18:32 by ywake             #+#    #+#             */
/*   Updated: 2020/07/08 12:08:29 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	free_set(char **dst, char *src)
{
	// printf("[free_set] %s\n", src);
	free(*dst);
	*dst = src;
}

int		ret(ssize_t rdrtn, char *rdbuf)
{
	free(rdbuf);
	if (rdrtn > 0)
		return (1);
	else
		return (rdrtn);
}

int		myabort(char *rdbuf, char **line, char **remain)
{
	free_set(&rdbuf, NULL);
	free_set(line, NULL);
	free_set(remain, NULL);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	char		*rdbuf;
	static char	*remain[1];
	char		*ptr;
	ssize_t		rtn;

	rdbuf = (char *)malloc(BUFFER_SIZE + 1);
	*line = ft_strndup(*remain, -1);
	free_set(remain, NULL);
	while ((rtn = read(fd, rdbuf, BUFFER_SIZE)) >= 0)
	{
		rdbuf[rtn] = '\0';
		// printf("[gnl > buf](%zd) '%s'\n", rtn, rdbuf);
		if (rtn == 0)
			free_set(line, ft_strjoin(*line, ""));
		else
			free_set(line, ft_strjoin(*line, (char *)rdbuf));
		if ((ptr = ft_strchr(*line, '\n')) != NULL)
		{
			free_set(remain, ft_strndup(ptr + 1, -1));
			// printf("[gnl > remain] '%s'\n", *remain);
			free_set(line, ft_strndup(*line, ptr - *line));
			return (ret(1, rdbuf));
		}
		if (rtn == 0)
			return (ret(0, rdbuf));
	}
	return (myabort(rdbuf, line, remain));
}
