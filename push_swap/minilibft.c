/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:02:28 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/18 12:59:05 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int ft_strlen(char *str)
{
  int i = 0;
  while (str[i])
    i++;
  return i;
}

char *ft_strdup(char *str)
{
  int i = 0;
  char *new;
  
  new = (char *) malloc(ft_strlen(str) + 1);
  while (str[i])
  {
    new[i] = str[i];
    i++;
  }
  new[i] = '\0';
  return new;
}

char *ft_strcat(char *dest, char *src)
{
  int i = 0, j = 0;
  int dlen = ft_strlen(dest);
  int slen = ft_strlen(src);
  char *new = (char *)malloc(dlen + slen + 2);
  
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
  return new;
}

char    *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
        size_t  i;
        size_t  j;

        i = 0;
        j = 0;
        if (!needle[j])
                return ((char *)haystack);
        while (haystack[i] && i < len)
        {
                j = 0;
                while (needle && needle[j] && \
                        haystack[j + i] && needle[j] == haystack[j + i] && i + j < len)
                        j++;
                if (!needle[j])
                        return ((char *)haystack + i);
                i++;
        }
        return (NULL);
}

long	ft_atol(const char *str)
{
	size_t	i;
	size_t	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if ((str[i] == '-' || str[i] == '+'))
		sign = (44 - str[i++]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + res * 10;
		i++;
	}
	return ((int)(res * sign));
}