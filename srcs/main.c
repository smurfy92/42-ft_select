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

int		main(int argc, char **argv)
{
	struct stat		bufstat;
	int				i;


	i = 0;
	while (++i < argc)
	{
		if (lstat(argv[i], &bufstat) == -1)
			ft_putendl("error");
		else
			ft_putendl(argv[i]);

	}
	return (0);
}
