/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:34:30 by iboubkri          #+#    #+#             */
/*   Updated: 2025/01/16 11:35:22 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void free_all(t_stks *stks)
{
    free(stks->a.content);
    free(stks->b.content);
    free(&stks->a);
    free(&stks->b);
    free(stks);
}