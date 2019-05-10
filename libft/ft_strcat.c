/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:18 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:58:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *dest, const char *src)
{
	if (!dest || !src)
		return ((void *)0);
	ft_strcpy(&dest[ft_strlen(dest)], src);
	return (dest);
}
