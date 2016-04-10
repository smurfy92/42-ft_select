/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 11:11:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/09 11:12:30 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include <sys/stat.h>
#include <termios.h>
#include <curses.h>
#include <term.h>

#define BUFFSIZE 3

typedef struct			s_lstfiles
{
	char				*name;
	int					selected;
	int					cursor;
	struct s_lstfiles	*next;
}						t_lstfiles;
