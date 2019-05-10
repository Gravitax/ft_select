/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:21 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:58:28 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strchr(const char *str, int c)
{
	const char ch = c;

	if (!str)
		return ((void *)0);
	while (*str != ch)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return ((char *)str);
}
