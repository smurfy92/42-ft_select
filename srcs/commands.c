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
	write(2, &c, 1);
	return (0);
}

void		ft_outstr(t_lstfiles *lst)
{
	if (lst->selected || lst->cursor)
		ft_putstr("\033[92m");
	write(2, lst->name, ft_strlen(lst->name));
	if (lst->selected || lst->cursor)
		ft_putstr("\033[0m");
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
			if (tmp->next)
				tmp->next->cursor = 1;
			else
				lst->cursor = 1;
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
	t_lstfiles *tmp;

	tmp = lst;
	while (lst)
	{
		if (lst->cursor)
		{
			if (lst->selected)
				lst->selected = 0;
			else
			{
				lst->selected = 1;
				lst->cursor = 0;
				if (lst->next)
					lst->next->cursor = 1;
				else
					tmp->cursor = 1;
			}
			break ;
		}
		lst = lst->next;
	}
}
