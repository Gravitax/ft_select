/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:11:37 by maboye            #+#    #+#             */
/*   Updated: 2019/05/08 12:43:09 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <curses.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# include "libft/libft.h"

# define CLEAR		"\e[1;1H\e[2J"

# define K_ENTER	10
# define K_ESC		27
# define K_SPC		32
# define K_BSP		127
# define K_UP		4283163
# define K_DOWN		4348699
# define K_RIGHT	4414235
# define K_LEFT		4479771
# define K_DEL		2117294875

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define TUR		"\033[36m"

typedef struct		s_node
{
	char			*name;
	int				index;
	int				current;
	int				token;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct		s_select
{
	struct termios	data;
	int				fd;
	int				column;
	int				row;
	int				max_len;
	int				lst_size;
	t_node			*args;
}					t_select;

t_node				*ft_dlstaddelem(t_node *prev);
void				ft_dlstdel(t_node **alst);
t_node				*ft_dlstget_current(t_node *list);
void				ft_dlstprint(t_node *list);
int					ft_dlstsize(t_node *list);

void				ft_display_column(t_select *term);
int					ft_error(char *str);
void				ft_freestruc(t_select **todel);
void				ft_move(int c);
void				ft_print_color(t_select *term, t_node *list);
void				ft_reset_term(t_select *term);
t_select			*ft_singleton(t_select *term, int init);
void				ft_term_loader(t_select	*term);

int					get_line_column(t_select *term, t_node *tmp, int choose);
void				load_term_size(t_select *term);
void				signal_handler(int sig);

int					my_putchar(int c);

#endif
