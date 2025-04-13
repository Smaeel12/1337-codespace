/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:11:57 by iboubkri          #+#    #+#             */
/*   Updated: 2025/04/12 18:22:38 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

suseconds_t getcurrenttime(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t to_number(char *input)
{
	size_t res;
	int sign;

	res = 0;
	sign = 1;
	if (!input || !*input)
		return (0);
	while (*input == ' ' || (*input >= '\t' && *input <= '\r'))
		input++;
	if (*input == '-' || *input == '+')
		sign = ',' - *input++;
	while (*input >= '0' && *input <= '9')
	{
		res = (res << 3) + (res << 1) + (*input - '0');
		input++;
	}
	return (res * (sign == 1) * !*input);
}
