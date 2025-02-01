/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:27:34 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/01 13:58:41 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_helper(char *lbuf, char *rbuf)
{
	char	*new;

	new = ft_strjoin(lbuf, rbuf);
	return (free(lbuf), new);
}

char	*get_next_line(int fd)
{
	static char	*lbuf;
	char		*rbuf;
	char		*pos;
	ssize_t		nb;

	rbuf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	while (1)
	{
		nb = read(fd, rbuf, BUFFER_SIZE);
		if (nb == -1)
			return (free(rbuf), free(lbuf), lbuf = NULL, NULL);
		rbuf[nb] = '\0';
		if (!nb)
			return (free(rbuf), rbuf = lbuf, lbuf = NULL, rbuf);
		lbuf = ft_strjoin_helper(lbuf, rbuf);
		pos = ft_strchr(lbuf, '\n');
		if (pos)
		{
			free(rbuf);
			rbuf = ft_substr(lbuf, 0, pos - lbuf + 1);
			ft_strlcpy(lbuf, pos + 1, ft_strlen(pos));
			return (rbuf);
		}
	}
}
