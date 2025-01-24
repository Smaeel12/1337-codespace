/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:34:30 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/20 09:03:54 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void ft_exit_error(t_stks *stks) {
    free(stks->a.content);
    free(stks->b.content);
    free(stks);
    exit(1);
}

int ft_is_sorted(t_stack stack)
{
    int i = 0;
    while (i < stack.len - 1)
    {
        if (stack.content[i] < stack.content[i + 1])
            return 0;
        i++;
    }
    return 1;
}