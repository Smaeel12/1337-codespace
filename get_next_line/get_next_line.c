/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:27:34 by iboubkri          #+#    #+#             */
/*   Updated: 2024/11/30 10:11:16 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*r_buffer;
	char		*l_buffer;
	ssize_t		nb;
	ssize_t		idx;

	nb = -1;
	idx = 0;
	l_buffer = NULL;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	init_buffer(&r_buffer, (size_t)BUFFER_SIZE + 1, sizeof(char));
	while (r_buffer)
	{
		idx += fill_line_buffer(r_buffer, &l_buffer);
		if (idx >= 0 && ((l_buffer && l_buffer[idx - 1] == '\n') || nb == 0))
			return (l_buffer);
		nb = read(fd, r_buffer, BUFFER_SIZE);
		if ((nb == -1 || (nb == 0 && !l_buffer)) || idx < 0)
			break ;
		r_buffer[nb] = '\0';
	}
	free(r_buffer);
	free(l_buffer);
	r_buffer = NULL;
	return (NULL);
}
