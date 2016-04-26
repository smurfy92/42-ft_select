/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 09:05:36 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/11 09:05:37 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			set_shell(int lflag)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = term.c_lflag & lflag;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &term))
		return (-1);
	return (0);
}

int			reset_shell(void)
{
	tputs(tgetstr("ve", NULL), 1, ft_outchar);
	if (tcsetattr(0, 0, NULL) == -1)
		return (-1);
	return (0);
}

int			init_shell(void)
{
	char	*name;

	signal(SIGWINCH, ft_handle_resize);
	signal(SIGINT, handler_ctrl);
	signal(SIGTSTP, handler_ctrl);
	signal(SIGCONT, handler_cont);
	if ((name = getenv("TERM")) == NULL)
		name = "xterm-256color";
	if (tgetent(NULL, name) == ERR)
		return (-1);
	return (1);
}

void		ft_clear_screen(t_term *term)
{
	tputs(tgetstr("cl", NULL), 2, ft_outchar);
	ft_display_lst(term);
}

void		ft_display_selection(t_lstfiles *lst)
{
	int t;

	t = 0;
	tputs(tgetstr("cl", NULL), 0, ft_outchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_outchar);
	while (lst)
	{
		if (lst->selected)
		{
			(t) ? ft_putchar(' ') : 0;
			ft_putstr(lst->name);
			t = 1;
		}
		lst = lst->next;
	}
	ft_putchar('\n');
	reset_shell();
	exit(0);
}
