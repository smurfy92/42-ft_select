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

void				ft_display_lst(t_lstfiles *lst)
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



t_lstfiles			*ft_create_lst(char *name)
{
	t_lstfiles		*lst;

	lst = (t_lstfiles*)malloc(sizeof(t_lstfiles));
	lst->name = ft_strdup(name);
	lst->selected = 0;
	lst->cursor = 0;
	lst->next = NULL;
	return (lst);
}

t_lstfiles			*ft_add_lst(t_lstfiles *tmp, t_lstfiles *lst)
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

t_lstfiles			*ft_del_lst(t_lstfiles *lst)
{
	t_lstfiles		*tmp;

	tmp = lst;
	if (tmp && tmp->cursor)
	{
		if (!tmp->next)
		{
			tgoto(NULL, 0, 0);
			tputs(tgetstr("cl", NULL), 0, ft_outchar);
			reset_shell();
			exit(0);
		}
		tmp->next->cursor = 1;
		return (tmp->next);
	}
	while (tmp)
	{
		if (tmp->next->cursor)
		{

			tmp->cursor = 1;
			tmp->next = tmp->next->next;
			break;
		}
		tmp = tmp->next;
	}
	return (lst);
}

void				ft_clear(t_lstfiles *lst)
{
	ft_clear_screen(lst);
	reset_shell();
}

static	t_lstfiles *ft_process(t_lstfiles *lst, char *buf)
{
	if (buf[0] == 127 || buf[0] == 126)
		lst = ft_del_lst(lst);
	else if (buf[0] == 10)
	{
		ft_clear(lst);
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
		{
			tputs(tgetstr("cl", NULL), 0, ft_outchar);
			reset_shell();
			exit(0);
		}
		else if (buf[2] == 65)
			ft_go_up(lst);
		else if (buf[2] == 66)
			ft_go_down(lst);
	}
	return (lst);
}
int					main(int argc, char **argv)
{
	struct stat			bufstat;
	int					i;
	char				buf[BUFF_SIZE];
	int					ret;
	static t_lstfiles	*lst;

	lst = NULL;
	init_shell();
	i = 0;
	set_shell((~ICANON & ~ECHO));
	while (++i < argc)
	{
		if (!(lstat(argv[i], &bufstat) == -1))
			lst = ft_add_lst(ft_create_lst(argv[i]), lst);
	}
	(!lst)? exit(0): 0;
	lst->cursor = 1;
	ft_clear_screen(lst);
	tputs(tgetstr("vi", NULL), 1, ft_outchar);
	while ((ret = read(0, buf, BUFFSIZE)))
	{
		set_shell((~ICANON & ~ECHO));
		lst = ft_process(lst, buf);
		ft_clear_screen(lst);
		ft_bzero(buf, ft_strlen(buf));
	}
	reset_shell();
	return (0);
}
