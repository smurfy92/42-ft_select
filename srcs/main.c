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
	int i;

	i = 0;
	while (lst)
	{
		ft_putendl(lst->name);
		lst = lst->next;
	}
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
	term.c_cc[VMIN] = 1; // nb de fois où la touche doit etre appuyé pour lancer la commande
	term.c_cc[VTIME] = 0; // retour de read tout les n délai*/
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
	if (tcsetattr(0, 0, NULL) == -1)
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

int		main(int argc, char **argv)
{
	struct stat		bufstat;
	int				i;
	char			buf[BUFF_SIZE];
	int				ret;
	t_lstfiles		*lst;


	lst = NULL;
	init_shell();
	i = 0;
	set_shell((~ICANON & ~ECHO));
	while (++i < argc)
	{
		if (!(lstat(argv[i], &bufstat) == -1))
			lst = ft_add_lst(ft_create_lst(argv[i]), lst);
	}
	ft_clear_screen(lst);
	ft_putstr(tgoto(tgetstr("cm", NULL), 0, 0));
	while ((ret = read(0, buf, BUFFSIZE)))
	{
		ft_clear_screen(lst);
		if (buf[0] == 27)
		{
			if (buf[1] == 0)
				return (0);
			else if (buf[2] == 65)
				ft_putendl("top arrow");
			else if (buf[2] == 68)
				ft_putendl("left arrow");
			else if (buf[2] == 67)
				ft_putendl("right arrow");
			else if (buf[2] == 66)
				ft_putendl("down arrow");
		}
		ft_putstr(tgoto(tgetstr("cm", NULL), 0, 0));
		ft_bzero(buf, ft_strlen(buf));
	}

	reset_shell();
	return (0);
}
