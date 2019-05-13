/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:12:22 by maboye            #+#    #+#             */
/*   Updated: 2019/05/08 16:09:06 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			print_token(t_select *term, t_node *list)
{
	t_node	*tmp;
	int		count;

	tmp = list->next;
	count = 0;
	while (tmp->next)
	{
		if (tmp->token)
			++count;
		if (tmp == list)
			break ;
		tmp = tmp->next;
	}
	while (count && list->next)
	{
		if (list->token)
		{
			ft_print_color(term, list);
			ft_putstr_fd(list->name, term->fd);
			ft_putstr_fd("\033[0m", term->fd);
			ft_putchar_fd(--count ? ' ' : '\n', term->fd);
		}
		list = list->next;
	}
}

static int			stock_args(t_node **tmp, char **av)
{
	t_node	*prev;
	int		i;
	int		len;

	i = 0;
	len = ft_tablen((void **)av);
	while (++i < len)
	{
		if (!ft_strlen(av[i]))
			continue ;
		if (!((*tmp)->name = ft_strdup(av[i])))
			return (0);
		(*tmp)->index = i;
		(*tmp)->current = 0;
		(*tmp)->token = 0;
		prev = *tmp;
		if (i < len - 1)
		{
			if (!((*tmp)->next = ft_dlstaddelem(prev)))
				return (0);
			*tmp = (*tmp)->next;
		}
	}
	return (1);
}

static int			handle_args(t_select **term, char **av)
{
	t_node	*tmp;

	if (!((*term)->args = ft_dlstaddelem(NULL)))
		return (0);
	tmp = (*term)->args;
	if (!(stock_args(&tmp, av)))
		return (0);
	(*term)->args->prev = tmp;
	tmp->next = (*term)->args;
	tmp->index = 0;
	(*term)->args->current = 1;
	ft_singleton(*term, 1);
	return (1);
}

/*
** rc : get last cursor position
** cd : clear everything under cursor
*/

static inline void	ft_read_input(t_select *term)
{
	char	buffer[5];

	while (42)
	{
		ft_bzero(buffer, 5);
		ft_display_column(term);
		if (read(0, buffer, 4) < 0)
			ft_error("read");
		ft_move(*(int *)buffer);
		if (*(int *)buffer == K_ESC || *(int *)buffer == 4)
			ft_error("EXIT");
		if (*(int *)buffer == K_ENTER)
			break ;
		tputs(tgetstr("rc", NULL), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
	}
}

int					main(int ac, char **av)
{
	t_select	*term;
	int			sig;

	if (ac > 1)
	{
		if (!(term = malloc(sizeof(t_select))))
			return (-1);
		sig = 0;
		while (++sig < 32)
			signal(sig, signal_handler);
		if (!(handle_args(&term, av)))
		{
			ft_freestruc(&term);
			return (-1);
		}
		ft_term_loader(term);
		ft_read_input(term);
		ft_reset_term(term);
		print_token(term, term->args);
		close(term->fd);
		ft_freestruc(&term);
	}
	else
		ft_putendl_fd("ft_select: usage: use arguments tarnation!", 2);
	return (0);
}
