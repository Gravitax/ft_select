/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:13:12 by maboye            #+#    #+#             */
/*   Updated: 2019/05/08 16:08:29 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static inline void	ft_padding(int nb, int fd)
{
	int		count;

	count = 0;
	while (nb >= 10)
	{
		nb -= 10;
		count++;
	}
	while (count--)
		write(fd, "          ", 10);
	write(fd, "          ", nb);
}

/*
** so : string to enter standout mode.
** se : string to leave standout mode.
** us : string to turn on underline mode
** ue : string to turn off underline mode
*/

static inline void	ft_set_color(t_select *term, t_node *tmp, char *str)
{
	if (tmp->token)
		tputs(tgetstr("so", NULL), 1, my_putchar);
	if (tmp->current)
	{
		tputs(tgetstr("us", NULL), 1, my_putchar);
		ft_putstr_fd(RED, term->fd);
		ft_putstr_fd(str, term->fd);
		ft_putstr_fd("\033[0m", term->fd);
		tputs(tgetstr("ue", NULL), 1, my_putchar);
	}
	else
	{
		ft_print_color(term, tmp);
		ft_putstr_fd(str, term->fd);
		ft_putstr_fd("\033[0m", term->fd);
	}
	if (tmp->token)
		tputs(tgetstr("se", NULL), 1, my_putchar);
}

static void			ft_never_too_small(t_select *term, t_node *tmp, char *str)
{
	int		i;

	i = 0;
	while (tmp->next)
	{
		++i;
		if ((int)ft_strlen(tmp->name) < term->column)
		{
			if (!(str = ft_strfjoin(ft_strdup(tmp->name), "\n", 1)))
				ft_error("malloc");
		}
		else
		{
			if (!(str = ft_strfjoin(ft_strsub(tmp->name,
			0, term->column - 4), "...\n", 1)))
				ft_error("malloc");
		}
		ft_set_color(term, tmp, str);
		ft_strdel(&str);
		if (!tmp->index || i >= term->row - 1)
			return ;
		tmp = tmp->next;
	}
}

static inline void	ft_display_helper(t_select *term, t_node *tmp, int column)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (tmp->next)
	{
		ft_set_color(term, tmp, tmp->name);
		tmp->index ? ft_padding(term->max_len
			- ft_strlen(tmp->name) + 1, term->fd) : 0;
		if (++i >= column - 1)
		{
			ft_putchar_fd('\n', term->fd);
			i = -1;
			++j;
		}
		if (!tmp->index || j >= term->row - 1)
			return ;
		tmp = tmp->next;
	}
}

void				ft_display_column(t_select *term)
{
	t_node	*tmp;
	int		column;
	int		i;

	ft_putstr_fd(CLEAR, term->fd);
	load_term_size(term);
	column = term->column / (term->max_len + 1) - 1;
	column = column <= 0 ? 1 : column;
	tmp = ft_dlstget_current(term->args);
	if (term->row < term->lst_size / column + 1)
		while (get_line_column(term, tmp, 1)
			- get_line_column(term, term->args, 1) > term->row - 2)
		{
			i = -1;
			while (++i < column)
				term->args = term->args->next;
		}
	tmp = term->args;
	if (term->max_len >= term->column)
		return (ft_never_too_small(term, tmp, NULL));
	ft_display_helper(term, tmp, column);
}
