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

int		ft_outchar(int c)
{
	return (write(1, &c, 1));
}

void			ft_display_lst(t_lstfiles *lst)
{
	int		i;
	char	*str;

	i = 0;
	while (lst)
	{

		str = tgoto(tgetstr("cm", NULL), 0, i++);
		tputs(str, 1, ft_outchar);
		if (lst->selected)
		{
			str = tgetstr("mr", NULL);
			tputs(str, 1, ft_outchar);
		}
		if (lst->cursor)
		{
			str = tgetstr("us", NULL);
			tputs(str, 1, ft_outchar);
		}
		ft_putstr(lst->name);
		str = tgetstr("me", NULL);
		tputs(str, 1, ft_outchar);
		lst = lst->next;
	}
	ft_putchar('\n');
}

void			ft_clear_screen(t_lstfiles *lst)
{
	char			*res;

	tgoto(NULL, 0, 0);
	if ((res = tgetstr("cl", NULL)) == NULL)
		exit(0);
	tputs(res, 0, ft_outchar);
	ft_display_lst(lst);
}

int		set_shell(int lflag)
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

t_lstfiles		*ft_create_lst(char *name)
{
	t_lstfiles		*lst;

	lst = (t_lstfiles*)malloc(sizeof(t_lstfiles));
	lst->name = ft_strdup(name);
	lst->selected = 0;
	lst->cursor = 0;
	lst->next = NULL;
	return (lst);
}

t_lstfiles		*ft_add_lst(t_lstfiles *tmp, t_lstfiles *lst)
{
	t_lstfiles		*tmp2;

	if (!lst)
		return (tmp);
	tmp2 = lst;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);
}

int		reset_shell()
{
	struct termios term;

	tputs(tgetstr("me", NULL), 1, ft_outchar);
	tputs(tgetstr("ve", NULL), 1, ft_outchar);
	if (tcgetattr(0, &term) == -1)
	   return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
	   return (-1);
	return (0);
}

int		init_shell()
{
	char	*name;

	if ((name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name) == ERR)
		return (-1);
	return (0);
}

void	ft_go_down(t_lstfiles *lst)
{
	while (lst)
	{
		if (lst->cursor && lst->next)
		{
			lst->cursor = 0;
			lst->next->cursor = 1;
			break;
		}
		lst = lst->next;
	}
}

void	ft_go_up(t_lstfiles *lst)
{
	while (lst->next)
	{
		if (lst->next->cursor)
		{
			lst->cursor = 1;
			lst->next->cursor = 0;
		}
		lst = lst->next;
	}
}

void	ft_select(t_lstfiles *lst)
{
	while (lst)
	{
		if (lst->cursor)
			(lst->selected) ? (lst->selected = 0) : (lst->selected = 1);
		lst = lst->next;
	}
}

void	ft_display_selection(t_lstfiles *lst)
{
	while (lst)
	{
		if (lst->selected)
		{
			ft_putstr(lst->name);
			ft_putchar(' ');
		}
		lst = lst->next;
	}
	exit(0);
}

int		main(int argc, char **argv)
{
	struct stat		bufstat;
	int				i;
	char			buf[BUFF_SIZE];
	int				ret;
	static t_lstfiles	*lst;


	lst = NULL;
	init_shell();
	i = 0;
	set_shell((~ICANON & ~ECHO));
	if (argc < 2)
	{
		ft_putendl("need arguments");
		exit(0);
	}
	while (++i < argc)
	{
		if (!(lstat(argv[i], &bufstat) == -1))
			lst = ft_add_lst(ft_create_lst(argv[i]), lst);
	}
	lst->cursor = 1;
	ft_clear_screen(lst);
	tputs(tgetstr("vi", NULL), 1, ft_outchar);
	while ((ret = read(0, buf, BUFFSIZE)))
	{
		set_shell((~ICANON & ~ECHO));
		if (buf[0] == 10)
		{
			ft_clear_screen(lst);
			reset_shell();
			ft_display_selection(lst);
		}
		else if (buf[0] == 32)
		{
			tputs(tgetstr("vb", NULL), 1, ft_outchar);
			ft_select(lst);
		}
		else if (buf[0] == 27)
		{
			if (buf[1] == 0)
				return (0);
			else if (buf[2] == 65)
				ft_go_up(lst);
			else if (buf[2] == 68)
				ft_putendl("left arrow");
			else if (buf[2] == 67)
				ft_putendl("right arrow");
			else if (buf[2] == 66)
				ft_go_down(lst);
		}
		ft_clear_screen(lst);
		ft_bzero(buf, ft_strlen(buf));
	}
	reset_shell();
	return (0);
}
