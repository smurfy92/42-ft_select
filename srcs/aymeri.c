/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aymeri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 15:47:46 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/11 15:47:46 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void				ft_handle_resize(int t)
{
	t = 0;
	ft_clear_screen(ft_get_term());
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

t_lstfiles			*ft_add_lst(t_term *term, t_lstfiles *tmp, t_lstfiles *lst)
{
	t_lstfiles		*tmp2;

	term->lstlen++;
	if (ft_strlen(tmp->name) > term->wordlen)
		term->wordlen = ft_strlen(tmp->name);
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
			break ;
		}
		tmp = tmp->next;
	}
	return (lst);
}

t_lstfiles			*ft_process(t_term *term, char *buf)
{
	t_lstfiles *lst;

	lst = term->lst;
	if (buf[0] == 127 || buf[0] == 126)
	{
		term->lstlen--;
		lst = ft_del_lst(lst);
	}
	else if (buf[0] == 10)
		ft_display_selection(lst);
	else if (buf[0] == 32)
	{
		tputs(tgetstr("vb", NULL), 1, ft_outchar);
		ft_select(lst);
	}
	else if (buf[0] == 27 && buf[1] == 0)
	{
		reset_shell();
		exit(0);
	}
	else if (buf[0] == 27 && buf[2] == 65)
		ft_go_up(lst);
	else if (buf[0] == 27 && buf[2] == 66)
		ft_go_down(lst);
	return (lst);
}
