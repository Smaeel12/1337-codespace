/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:06:38 by iboubkri          #+#    #+#             */
/*   Updated: 2025/02/10 17:50:29 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_get_node(t_list *lst, int idx)
{
	int	i;

	i = 0;
	while (lst && i < idx)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
