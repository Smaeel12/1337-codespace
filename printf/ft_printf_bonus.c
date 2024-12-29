/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboubkri <iboubkri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:15:12 by iboubkri          #+#    #+#             */
/*   Updated: 2024/12/29 09:07:46 by iboubkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_charfuncs(va_list args, char ps, int *nc)
{
	size_t	len;
	char	*str;

	if (ps == '%')
		*nc += (write(1, "%", 1));
	else if (ps == 'c')
		*nc += (write(1, &((char []){va_arg(args, int)}), 1));
	else if (ps == 's')
	{
		len = 0;
		str = va_arg(args, char *);
		if (!str)
			*nc += (write(1, "(null)", 6));
		else
		{
			while (str[len])
				len++;
			*nc += write(1, str, len);
		}
	}
	else
		return (0);
	return (1);
}

int	ft_putnbr(unsigned long int n, t_bs bs)
{
	if (n < (unsigned long)bs.lb)
		return (write(1, &bs.bs[n % bs.lb], 1));
	return (ft_putnbr(n / bs.lb, bs) + write(1, &bs.bs[n % bs.lb], 1));
}

int	ft_printaddr(unsigned long addr, t_bs bs)
{
	if (addr == 0)
		return (write(1, "(nil)", 5));
	else
		return (write(1, bs.pre, 2) + ft_putnbr(addr, bs));
}

int	ft_numfuncs(va_list args, char ps, char flag, int *nc)
{
	long	n;
	t_bs	bs;

	bs = (t_bss){.bss = {{"0123456789", 10, ""}, {"0123456789abcdef", 16, "0x"},
	{"0123456789ABCDEF", 16, "0X"}}}.bss[(ps == 'x'
			|| ps == 'p') | (1 << (ps == 'X')) * (ps == 'X')];
	if (ps == 'u' || ps == 'x' || ps == 'X')
	{
		n = va_arg(args, unsigned int);
		*nc += (write(1, bs.pre, 2 * (bs.pre[0] && flag == '#' && !(!n)))
				+ ft_putnbr(n, bs));
	}
	else if (ps == 'd' || ps == 'i')
	{
		n = va_arg(args, int);
		*nc += (write(1, &"-+ "[(n >= 0) * (1 << (flag == ' '))], (n < 0
						|| (flag == ' ') | (flag == '+'))) + ft_putnbr((n
						* ((n < 0) * -1 | 1)), bs));
	}
	else if (ps == 'p')
		*nc += ft_printaddr((unsigned long)va_arg(args, void *), bs);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		nc;
	char	flag;

	nc = 0;
	va_start(args, format);
	while (*format)
	{
		flag = '\0';
		if (*format == '%')
		{
			if (*++format == ' ' || *format == '#' || *format == '+')
				flag = *format++;
			if (!ft_numfuncs(args, *format, flag, &nc) && !ft_charfuncs(args,
					*format, &nc))
				return (write(1, (char []){'%', *format}, 2));
		}
		else
			nc += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (nc);
}
