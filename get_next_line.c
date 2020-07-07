/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:18:32 by ywake             #+#    #+#             */
/*   Updated: 2020/07/07 19:35:17 by ywake            ###   ########.fr       */
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

int		get_next_line(int fd, char **line)
{
	char		rdbuf[BUFFER_SIZE + 1];
	static char	*remain[1];
	char		*ptr;
	ssize_t		rtn;

	*line = ft_strndup(*remain, -1);
	free_set(remain, NULL);
	while ((rtn = read(fd, rdbuf, BUFFER_SIZE)) >= 0)
	{
		rdbuf[rtn] = '\0';
		if (rtn > 0)
			free_set(line, ft_strjoin(*line, (char *)rdbuf));
		if ((ptr = ft_strchr(*line, '\n')) != NULL)
		{
			free_set(remain, ft_strndup(ptr + 1, -1));
			// printf("[gnl > remain] '%s'\n", *remain);
			free_set(line, ft_strndup(*line, ptr - *line));
			return (1);
		}
		if (rtn == 0)
			return (0);
	}
	if (rtn == -1)
		free_set(line, NULL);
	free_set(remain, NULL);
	return (rtn);
}
