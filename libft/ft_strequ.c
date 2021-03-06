/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:19:45 by jtranchi          #+#    #+#             */
/*   Updated: 2015/12/03 15:19:46 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int		i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i])
		{
			if (s1[i] == '\0')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (0);
}
