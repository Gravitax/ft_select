/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:29:28 by maboye            #+#    #+#             */
/*   Updated: 2019/05/13 15:39:39 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		get_larger_word(t_node *list)
{
	int		len;

	len = 0;
	while (list->next)
	{
		len = len > (int)ft_strlen(list->name) ? len : ft_strlen(list->name);
		if (!list->index)
			return (len);
		list = list->next;
	}
	return (len);
}

void			load_term_size(t_select *term)
{
	struct winsize	window;

	while (term->args->prev)
	{
		if (!term->args->prev->index)
			break ;
		term->args = term->args->prev;
	}
	ioctl(STDERR_FILENO, TIOCGWINSZ, &window);
	term->column = window.ws_col;
	term->row = window.ws_row;
	term->lst_size = ft_dlstsize(term->args);
	term->max_len = get_larger_word(term->args);
	if (!term->max_len)
		ft_error("invalid arguments");
}

/*
** cl : clear screen && cursor set top left corner //te
** sc : save cursor current position
** ve : cursor to normal
** vi : make cursor invisible //ti
*/

void			ft_term_loader(t_select *term)
{
	if (!isatty(0))
		ft_error("FATAL");
	term->fd = 0;
	if ((term->fd = open(ttyname(0), O_RDWR)) == -1)
		ft_error("FATAL");
	if (tgetent(NULL, getenv("TERM")) < 1)
		ft_error("FATAL");
	if (tcgetattr(term->fd, &(term->data)) == -1)
		ft_error("FATAL");
	term->data.c_lflag &= ~(ICANON);
	term->data.c_lflag &= ~(ECHO);
	term->data.c_cc[VMIN] = 1;
	term->data.c_cc[VTIME] = 0;
	if (tcsetattr(term->fd, TCSADRAIN, &(term->data)) == -1)
		ft_error("tcsetattr");
	tputs(tgetstr("vi", NULL), 1, my_putchar);
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
}

void			ft_reset_term(t_select *term)
{
	if (tcgetattr(term->fd, &(term->data)) == -1)
		ft_error("tcgetattr");
	term->data.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(term->fd, TCSANOW, &(term->data)) == -1)
		ft_error("tcseattr");
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	tputs(tgetstr("ve", NULL), 1, my_putchar);
}
