/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:17:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/31 14:49:48 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(ft_strlen(dest) + ft_strlen(src) + 2);
	if (!new)
		return (NULL);
	while (dest[i])
	{
		new[i] = dest[i];
		i++;
	}
	new[i++] = ' ';
	while (src[j])
	{
		new[i + j] = src[j];
		j++;
	}
	new[i + j] = '\0';
	free(dest);
	return (new);
}
