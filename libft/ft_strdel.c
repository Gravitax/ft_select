/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:37:05 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:45:12 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_strdel(char **as)
{
	if (!as || !*as)
		return ;
	free(*as);
	*as = 0;
}
