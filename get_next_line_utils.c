/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:38:08 by ywake             #+#    #+#             */
/*   Updated: 2020/07/08 12:14:43 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
		len++;
	len = (len < n) ? len : n;
	if ((ptr = (char *)malloc(len + 1 * sizeof(char))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	bufsize;
	char	*buf;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	while (s1 != NULL && s1[len1])
		len1++;
	len2 = 0;
	while (s2 != NULL && s2[len2])
		len2++;
	bufsize = len1 + len2 + 1;
	if ((buf = (char *)malloc(bufsize * sizeof(char))) == NULL)
		return (NULL);
	len1 = 0;
	while (s1 != NULL && *s1)
		buf[len1++] = *s1++;
	len2 = 0;
	while (s2 != NULL && *s2)
		buf[len1 + len2++] = *s2++;
	buf[len1 + len2] = '\0';
	return (buf);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}
