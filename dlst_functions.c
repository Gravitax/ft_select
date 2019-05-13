/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:32:39 by maboye            #+#    #+#             */
/*   Updated: 2019/05/06 14:15:51 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_node			*ft_dlstaddelem(t_node *prev)
{
	t_node	*elem;

	if (!(elem = malloc(sizeof(t_node))))
		return (NULL);
	elem->name = NULL;
	elem->prev = prev;
	elem->next = NULL;
	return (elem);
}

void			ft_dlstdel(t_node **alst)
{
	if (alst)
	{
		if ((*alst)->index)
			ft_dlstdel(&((*alst)->next));
		ft_strdel(&((*alst)->name));
		ft_memdel((void **)alst);
	}
}

t_node			*ft_dlstget_current(t_node *list)
{
	t_node	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp->next)
	{
		if (tmp->current == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			ft_dlstprint(t_node *list)
{
	if (!list)
		return ;
	while (list)
	{
		ft_putendl(list->name);
		if (!list->index)
			return ;
		list = list->next;
	}
}

int				ft_dlstsize(t_node *list)
{
	int		count;

	count = 0;
	if (!list)
		return (count);
	while (list->next)
	{
		++count;
		if (!list->index)
			return (count);
		list = list->next;
	}
	return (count);
}
