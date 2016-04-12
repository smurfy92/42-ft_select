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

	i = 0;
	while (lst)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, i++), 1, ft_outchar);
		if (lst->selected)
			tputs(tgetstr("mr", NULL), 1, ft_outchar);
		if (lst->cursor)
			tputs(tgetstr("us", NULL), 1, ft_outchar);
		ft_putstr(lst->name);
		tputs(tgetstr("me", NULL), 1, ft_outchar);
		lst = lst->next;
	}
	ft_putchar('\n');
}

int					main(int argc, char **argv)
{
	struct stat			bufstat;
	int					i;
	char				buf[BUFF_SIZE];
	int					ret;
	static t_lstfiles	*lst;

	lst = NULL;
	(init_shell()) ? set_shell((~ICANON & ~ECHO)) : 0;
	i = 0;
	while (++i < argc)
		if (!(lstat(argv[i], &bufstat) == -1))
			lst = ft_add_lst(ft_create_lst(argv[i]), lst);
	(!lst) ? exit(0) : 0;
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
