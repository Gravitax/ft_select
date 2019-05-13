/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:23:03 by maboye            #+#    #+#             */
/*   Updated: 2019/05/13 16:17:15 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				ft_error(char *str)
{
	t_select	*term;

	term = NULL;
	term = ft_singleton(term, 0);
	if (ft_strcmp(str, "FATAL"))
		ft_reset_term(term);
	ft_putstr_fd(CLEAR, term->fd);
	close(term->fd);
	if (ft_strcmp(str, "EXIT"))
	{
		ft_putstr_fd(CLEAR, 2);
		ft_putstr_fd("ft_select: error: ", 2);
		ft_putendl_fd(str, 2);
	}
	ft_freestruc(&term);
	exit(0);
}

void			ft_freestruc(t_select **todel)
{
	t_node	*tmp;

	if (todel)
	{
		if (*todel)
		{
			tmp = (*todel)->args;
			if (tmp)
			{
				while (tmp->prev)
				{
					if (!tmp->prev->index)
						break ;
					tmp = tmp->prev;
				}
				ft_dlstdel(&tmp);
			}
		}
		ft_memdel((void **)todel);
	}
}

void			ft_print_color(t_select *term, t_node *list)
{
	struct stat	elem;
	char		*path;
	char		stock[BUFF_SIZE + 1];

	ft_bzero(stock, BUFF_SIZE);
	if (!(path = ft_strjoin(getcwd(stock, BUFF_SIZE), "/")))
		ft_error("malloc");
	if (!(path = ft_strfjoin(path, list->name, 1)))
		ft_error("malloc");
	if (!lstat(list->name, &elem) || !lstat(path, &elem))
	{
		if (S_ISDIR(elem.st_mode) && !S_ISLNK(elem.st_mode))
			ft_putstr_fd(TUR, term->fd);
		else if (S_ISBLK(elem.st_mode))
			ft_putstr_fd(GREEN, term->fd);
		else if (S_ISCHR(elem.st_mode))
			ft_putstr_fd(YELLOW, term->fd);
		else if (S_ISLNK(elem.st_mode))
			ft_putstr_fd(PURPLE, term->fd);
		else
			ft_putstr_fd(BLUE, term->fd);
	}
	else
		ft_putstr_fd(BLUE, term->fd);
	ft_strdel(&path);
}

t_select		*ft_singleton(t_select *term, int init)
{
	static t_select	*save = NULL;

	if (init)
		save = term;
	return (save);
}

int				my_putchar(int c)
{
	return (write(2, &c, 1));
}
