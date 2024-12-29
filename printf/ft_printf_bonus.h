/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:15:59 by iboubkri          #+#    #+#             */
/*   Updated: 2024/12/29 09:07:13 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include <unistd.h>

typedef struct s_conver
{
	char	flag;
	char	cv;
}			t_conver;

typedef struct s_bs
{
	char	*bs;
	int		lb;
	char	*pre;
}			t_bs;

typedef struct s_bss
{
	t_bs	bss[3];
}			t_bss;

int			ft_printf(const char *format, ...);

#endif