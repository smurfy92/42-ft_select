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

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define BUFFSIZE 3

typedef struct			s_lstfiles
{
	char				*name;
	int					selected;
	int					cursor;
	struct s_lstfiles	*next;
}						t_lstfiles;

typedef struct			s_term
{
	char				*name;
	int					lstlen;
	size_t				wordlen;
	char				buf[BUFF_SIZE];
	struct s_lstfiles	*lst;

}						t_term;

t_lstfiles				*ft_create_lst(char *name);
t_lstfiles				*ft_add_lst(t_term *term, t_lstfiles *tmp,\
t_lstfiles *lst);
t_lstfiles				*ft_del_lst(t_lstfiles *lst);
t_lstfiles				*ft_process(t_term *term, char *buf);
int						ft_outchar(int c);
int						set_shell(int lflag);
int						reset_shell(void);
int						init_shell(void);
void					handler_ctrl(int sig);
void					handler_cont(int sig);
void					ft_handle_resize(int t);
void					ft_outstr(char *str);
void					ft_display_lst(t_term *term);
void					ft_go_up(t_lstfiles *lst);
void					ft_select(t_lstfiles *lst);
void					ft_display_selection(t_lstfiles *lst);
void					ft_go_down(t_lstfiles *lst);
void					ft_clear_screen(t_term *term);

#endif
