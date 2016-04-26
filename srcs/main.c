/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 11:09:47 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/09 11:12:08 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void		ft_display_lst(t_term *term)
{
	int				i;
	t_lstfiles		*lst;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	lst = term->lst;
	if (((((term->lstlen + 2) / w.ws_row) + 1) * term->wordlen) >= w.ws_col - 2)
	{
		ft_outstr("window too small");
		return ;
	}
	i = 0;
	while (lst)
	{
		tputs(tgoto(tgetstr("cm", NULL), (term->wordlen + 2) *\
		(i / w.ws_row), i % w.ws_row), 1, ft_outchar);
		i++;
		if (lst->selected)
			tputs(tgetstr("mr", NULL), 1, ft_outchar);
		(lst->cursor) ? tputs(tgetstr("us", NULL), 2, ft_outchar) : 0;
		ft_outstr(lst->name);
		tputs(tgetstr("me", NULL), 1, ft_outchar);
		lst = lst->next;
	}
	ft_outchar((int)'\n');
}

t_term		*ft_get_term(void)
{
	static	t_term		*term;

	if (!term)
	{
		term = (t_term*)malloc(sizeof(t_term));
		term->lst = NULL;
		term->wordlen = 0;
		term->lstlen = 0;
	}
	return (term);
}

void		handler_cont(int sig)
{
	t_term *term;

	sig = 0;
	init_shell();
	set_shell((~ICANON & ~ECHO));
	tputs(tgetstr("vi", NULL), 1, ft_outchar);
	term = ft_get_term();
	ft_clear_screen(term);
}

void		handler_ctrl(int sig)
{
	char	order[2];

	order[0] = sig == SIGTSTP ? 26 : 3;
	order[1] = 0;
	reset_shell();
	signal(sig, SIG_DFL);
	ioctl(0, TIOCSTI, order);
}

int			main(int argc, char **argv)
{
	struct stat			bufstat;
	int					i;
	int					ret;
	static	t_term		*term;

	term = ft_get_term();
	(init_shell()) ? set_shell((~ICANON & ~ECHO)) : 0;
	i = 0;
	while (++i < argc)
		if (!(lstat(argv[i], &bufstat) == -1))
			term->lst = ft_add_lst(term, ft_create_lst(argv[i]), term->lst);
	(!term->lst) ? exit(0) : 0;
	term->lst->cursor = 1;
	tputs(tgetstr("vi", NULL), 1, ft_outchar);
	tputs(tgetstr("cl", NULL), 0, ft_outchar);
	ft_display_lst(term);
	while ((ret = read(0, term->buf, BUFFSIZE)))
	{
		set_shell((~ICANON & ~ECHO));
		term->lst = ft_process(term, term->buf);
		ft_clear_screen(term);
		ft_bzero(term->buf, ft_strlen(term->buf));
	}
	reset_shell();
	return (0);
}
