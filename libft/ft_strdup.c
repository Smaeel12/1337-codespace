/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:53:56 by iboubkri          #+#    #+#             */
/*   Updated: 2024/10/29 20:11:42 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*dup;

	slen = 0;
	dup = NULL;
	slen = ft_strlen(s1);
	dup = (char *)malloc(slen * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, slen + 1);
	return (dup);
}
