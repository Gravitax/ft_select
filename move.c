/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:31:24 by maboye            #+#    #+#             */
/*   Updated: 2019/05/08 12:34:47 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			ft_move_delone(t_select *term, t_node *tmp)
{
	if (tmp->next == tmp)
		ft_error("EXIT");
	if (!tmp->index)
		tmp->prev->index = 0;
	tmp->next->current = 1;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	if (tmp == term->args)
		term->args = term->args->next;
	ft_strdel(&tmp->name);
	ft_memdel((void **)&tmp);
}

int					get_line_column(t_select *term, t_node *tmp, int choose)
{
	int		column;

	column = term->column / (term->max_len + 1) - 1;
	column = column <= 0 ? 1 : column;
	if (choose)
	{
		if (!tmp->index)
			return (term->lst_size / column + 1);
		return ((tmp->index - 1) / column + 1);
	}
	if (!tmp->index)
		return (term->lst_size % column ? term->lst_size % column : column);
	return ((tmp->index - 1) % column + 1);
}

static void			ft_move_down(t_select *term, t_node *tmp)
{
	int		i;
	int		column;
	t_node	*last;

	last = tmp;
	while (last->next)
	{
		if (!last->index)
			break ;
		last = last->next;
	}
	column = term->column / (term->max_len + 1) - 1;
	tmp->current = 0;
	i = 0;
	if (get_line_column(term, tmp, 1) == get_line_column(term, last, 1))
		column = get_line_column(term, last, 0);
	else if (get_line_column(term, tmp, 1)
		== get_line_column(term, last, 1) - 1)
	{
		if (get_line_column(term, tmp, 0) > get_line_column(term, last, 0))
			column = get_line_column(term, last, 0) + column;
	}
	while (++i < column)
		tmp = tmp->next;
	tmp->next->current = 1;
}

static void			ft_move_up(t_select *term, t_node *tmp)
{
	int		i;
	int		column;
	t_node	*last;

	last = tmp;
	while (last->next)
	{
		if (!last->index)
			break ;
		last = last->next;
	}
	column = term->column / (term->max_len + 1) - 1;
	tmp->current = 0;
	i = 0;
	if (get_line_column(term, tmp, 1) == 1)
	{
		if (get_line_column(term, tmp, 0) > get_line_column(term, last, 0))
			column = get_line_column(term, last, 0) + column;
		else
			column = get_line_column(term, last, 0);
	}
	while (++i < column)
		tmp = tmp->prev;
	tmp->prev->current = 1;
}

void				ft_move(int c)
{
	t_select	*term;
	t_node		*tmp;

	term = NULL;
	term = ft_singleton(term, 0);
	tmp = ft_dlstget_current(term->args);
	if (c == K_BSP || c == K_DEL)
		ft_move_delone(term, tmp);
	if (c == K_SPC)
	{
		tmp->current = 0;
		tmp->next->current = 1;
		tmp->token = tmp->token ? 0 : 1;
	}
	if (c == K_UP || c == K_DOWN)
		c == K_UP ? ft_move_up(term, tmp) : ft_move_down(term, tmp);
	if (c == K_RIGHT || c == K_LEFT)
	{
		tmp->current = 0;
		if (c == K_RIGHT)
			tmp->next->current = 1;
		if (c == K_LEFT)
			tmp->prev->current = 1;
	}
}
