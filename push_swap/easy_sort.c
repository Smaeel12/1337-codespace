/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:13:49 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/16 11:51:09 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define TOP *alen - 1

int ft_issorted(t_stack stack)
{
    int i = 0;
    while (i < stack.len - 1)
    {
        if (stack.content[i] > stack.content[i + 1])
            return 0;
    }
    return 1;
}

void easy_sort(t_stks *stks) {

    while (!ft_issorted(stks->a)) {
        if (ft_issorted(sa) && blen) {
            push_stack(sa, alen, sb, &blen);
        }
        if (sa[TOP] > sa[TOP - 1])
        {
            if (sa[TOP] > sa[0]) {
                
            }
        }
    }
}