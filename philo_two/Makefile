# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 10:47:13 by pmelinda          #+#    #+#              #
#    Updated: 2021/03/13 11:00:52 by pmelinda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo_two

SRC= ft_atoi.c\
		ft_putstr_fd.c\
		ft_strlen.c\
		logs.c\
		main.c\
		philos_utilities.c\
		sleep_in_ms.c\
		table.c\
		time_unix_seconds.c

HEADERS= philo_two.h

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
		clang -Wall -Wextra -Werror -pthread $(SRC) -o $(NAME)

clean:
		rm -rf $(NAME)

fclean: clean

re: fclean all

norm:
		norminette *.c *.h
