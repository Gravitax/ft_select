/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:07:59 by maboye            #+#    #+#             */
/*   Updated: 2019/05/04 13:36:44 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void			handle_percent(va_list args, int choose)
{
	char	*str;
	int		nb;
	char	c;

	if (!choose)
	{
		str = va_arg(args, char*);
		str ? ft_putstr(str) : 0;
	}
	else if (choose == 1)
	{
		nb = va_arg(args, int);
		ft_putnbr(nb);
	}
	else if (choose == 2)
	{
		c = va_arg(args, int);
		ft_putchar(c);
	}
}

void				ft_printf(const char *str, ...)
{
	va_list	args;

	if (!str)
		return ;
	va_start(args, str);
	while (str && *str)
	{
		if (*str == '%')
		{
			*(str + 1) == 's' ? handle_percent(args, 0) : 0;
			*(str + 1) == 'd' ? handle_percent(args, 1) : 0;
			*(str + 1) == 'c' ? handle_percent(args, 2) : 0;
			str += 2;
		}
		else
			ft_putchar(*str++);
	}
	va_end(args);
}
