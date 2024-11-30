/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:38:05 by iboubkri          #+#    #+#             */
/*   Updated: 2024/11/30 10:11:11 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src && dst && src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*init_buffer(char **ptr, size_t nmemb, size_t size)
{
	if (*ptr)
		return (*ptr);
	*ptr = (char *)malloc((nmemb * size) * sizeof(char));
	if (!*ptr)
		return (NULL);
	while (nmemb--)
		(*ptr)[nmemb] = '\0';
	return (*ptr);
}

ssize_t	newline_positon(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == (char)c)
			return (i);
	}
	return (i);
}

ssize_t	fill_line_buffer(char *r_buffer, char **l_buffer)
{
	ssize_t	pos;
	ssize_t	l_len;
	char	*ptr;

	pos = newline_positon(r_buffer, '\n');
	if (!pos)
		return (0);
	l_len = ft_strlen((*l_buffer));
	ptr = (char *)malloc((pos + l_len + 1) * sizeof(char));
	if (!ptr)
		return (-1);
	ft_strlcpy(ptr, (*l_buffer), l_len + 1);
	ft_strlcpy(ptr + l_len, r_buffer, pos);
	ft_strlcpy(r_buffer, r_buffer + pos, ft_strlen(r_buffer) - pos + 1);
	free((*l_buffer));
	(*l_buffer) = ptr;
	return (pos);
}
