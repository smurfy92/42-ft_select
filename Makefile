# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/09 10:58:04 by jtranchi          #+#    #+#              #
#    Updated: 2016/04/09 10:58:09 by jtranchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
LIB = libft/libft.a
SRC =	srcs/main.c \
		srcs/commands.c \
		srcs/shell.c \
		srcs/aymeri.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: start $(NAME)

$(NAME): $(OBJ)
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Creating Library$(CE)";
	-@make -C libft nohd
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Compiling ft_select ...$(CE)";
	@gcc -o $(NAME) $(FLAG) $(SRC) $(LIB) -lncurses

%.o: %.c
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Compiling $<$(CE)";
	@gcc $(FLAG) -c $< -o $@

start:
	@echo "\n\n"
	@echo "					$(CG)                          00000000000000000000$(CE)";
	@echo "					$(CG)                       00000000000000000000000000$(CE)";
	@echo "					$(CG)                    000000000000000000000000000000000         00   0000$(CE)";
	@echo "					$(CG)    000000        00000000000000000000000000000000000000       000000000$(CE)";
	@echo "					$(CG) 00 000000      0000000000    0000000000000    0000000000       0000000$(CE)";
	@echo "					$(CG) 000000000     0000000000      00000000000      00000000000    0000000$(CE)";
	@echo "					$(CG)   0000000    00000000000      00000000000      0000000000000000000000$(CE)";
	@echo "					$(CG)   00000000000000000000000    0000000000000    00000000000000  00000$(CE)";
	@echo "					$(CG)    000000000000000000000000000000000000000000000000000000000     000$(CE)";
	@echo "					$(CG)     000   000000000000000000000000000000000000000000000000000     0000$(CE)";
	@echo "					$(CG)    0000   000000000000000000000000000000000000000000000000000       000$(CE)";
	@echo "					$(CG)    000    0000000000000000000000000000000000000000000000 0000000000000000$(CE)";
	@echo "					$(CG)   0000000000000  0000000000000000000000000000000000000   00000000000000000$(CE)";
	@echo "					$(CG)   0000000000000   0000000000000000000000000000000000     00000000000$(CE)";
	@echo "					$(CG)  0000       0000    000000000000000000000000000000      000$(CE)";
	@echo "					$(CG)             00000     0000000000000000000000000         00$(CE)";
	@echo "					$(CG)               0000          000000000000000           000$(CE)";
	@echo "					$(CG)                00000                                0000$(CE)";
	@echo "					$(CG)                 000000      00000000000000        0000$(CE)";
	@echo "					$(CG)                   00000000     0000000000000   000000$(CE)";
	@echo "					$(CG)                      00000000000  0000000000000000$(CE)";
	@echo "					$(CG)                         000000000000000000000$(CE)";
	@echo "					$(CG)                                 00000000000000$(CE)";
	@echo "					$(CG)                                     00000000000$(CE)";
	@echo "					$(CG)                                      0000000000$(CE)";
	@echo "					$(CG)                                       0000000$(CE)";
	@echo "\n\n"
	@echo "							$(CG)  __  _                _              _$(CE)";
	@echo "							$(CG) / _|| |              | |            | |$(CE)";
	@echo "							$(CG)| |_ | |_   ___   ___ | |  ___   ___ | |_$(CE)";
	@echo "							$(CG)|  _|| __| / __| / _ \| | / _ \ / __|| __|$(CE)";
	@echo "							$(CG)| |  | |_  \__ \|  __/| ||  __/| (__ | |_$(CE)";
	@echo "							$(CG)|_|   \__| |___/ \___||_| \___| \___| \__|$(CE)";


clean: start
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Cleaning Library ...$(CE)";
	-@make -C libft nohdclean
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Cleaning ft_select objects$(CE)";
	@/bin/rm -rf $(OBJ)

fclean: start clean
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)FCleaning Library ...$(CE)";
	-@make -C libft nohdfclean
	@echo "$(CY)[FT_SELECT] :$(CE) $(CG)Cleaning ft_select ...$(CE)";
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
