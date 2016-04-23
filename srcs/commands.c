/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 09:04:19 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/11 09:04:20 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			ft_outchar(int c)
{

	return (write(1, &c, 1));
}

void		ft_go_down(t_lstfiles *lst)
{
	t_lstfiles *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->cursor && tmp->next)
		{
			tmp->cursor = 0;
			tmp->next->cursor = 1;
			break ;
		}
		if (tmp->cursor && !tmp->next)
		{
			lst->cursor = 1;
			tmp->cursor = 0;
			break ;
		}
		tmp = tmp->next;
	}
}

void		ft_go_up(t_lstfiles *lst)
{
	if (lst->cursor)
	{
		lst->cursor = 0;
		while (lst->next)
			lst = lst->next;
		lst->cursor = 1;
		return ;
	}
	while (lst)
	{
		if (lst->next && lst->next->cursor)
		{
			lst->cursor = 1;
			lst->next->cursor = 0;
		}
		lst = lst->next;
	}
}

void		ft_select(t_lstfiles *lst)
{
	while (lst)
	{
		if (lst->cursor)
			lst->selected = (lst->selected ? 0 : 1);
		lst = lst->next;
	}
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
