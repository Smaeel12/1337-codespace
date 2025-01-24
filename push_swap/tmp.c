/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:59:10 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/17 14:52:14 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// long	ft_atol(const char *str)
// {
// 	size_t	i;
// 	size_t	res;
// 	int		sign;

// 	i = 0;
// 	res = 0;
// 	sign = 1;
// 	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
// 		i++;
// 	if ((str[i] == '-' || str[i] == '+'))
// 		sign = (44 - str[i++]);
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = (str[i] - '0') + res * 10;
// 		i++;
// 	}
// 	return ((int)(res * sign));
// }

// int ft_is_digit(char *str) {
//     int i;

//     i = 0;
// 	if ((str[i] == '-' || str[i] == '+'))
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] < '0' && str[i] > '9')
//             return 0;
//         i++;
// 	}
//     return 1;
// }

// int ft_count_args(char **args) {
//     int i;

//     i = 0;
//     while (args[i])
//         i++;
//     return i;
// }

// int validate_arg(char *arg)
// {
//     int i = 0;
//     int num;

//     if (arg[i])
//     {
//         while (arg[i] == ' ')
//             i++;
//         if (!ft_is_digit(arg[i]))
//             return 0;
//         i++;
//     }
    
// }

size_t  ft_strlcat(char *dst, const char *src, size_t dstsize)
{
        size_t  i;
        size_t  dstlen;
        size_t  srclen;

        i = 0;
        srclen = ft_strlen(src);
        if (!dst && !dstsize)
                return (srclen);
        dstlen = ft_strlen(dst);
        while (dst && src[i] && dstsize > dstlen && i < dstsize - dstlen - 1)
        {
                dst[dstlen + i] = src[i];
                i++;
        }
        if (dstsize > dstlen)
                dstsize = dstlen;
        if (dst)
                dst[dstlen + i] = '\0';
        return (srclen + dstsize);
}


int ft_space_concatenate(char **line, char *arg, int len)
{
    char *new_line;
    int arg_len;

    arg_len = ft_strlen(arg);
    *new_line = (char *) malloc((len + arg_len)* sizeof(char));
    len += ft_strlcat(*new_line, line, len);
    len += ft_strlcat(*new_line, arg, arg_len);
    free(line);
    return len;
}

char *create_args_line(char **args)
{
    int len;
    int i;
    char *line;

    line = "";
    while (args[i])
    {
        len = ft_space_concatenate(&line, args[i], len);
        i++;
    }
    return line;
}

int ft_process_args(t_stks *stks, char **args) {
    int i;
    int num;
    char *list;

    i = 0;
    list = join_args(args);
    stks->a.len = ft_count_args(args);
    stks->a.content = malloc(stks->a.len * sizeof(int));
    stks->b.content = malloc(stks->a.len * sizeof(int));
    if (!stks->a.content)
        return 0;
    args = ft_parse_args(args);
    while (args[i])
    {
        num = ft_atol(args[i]);
        if (num == 0 && !ft_is_digit(args[i]))
                return 0;
        stks->a.content[i] = num;
        i++;
    }
    return 1;
}