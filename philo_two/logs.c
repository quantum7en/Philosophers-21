/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:58:04 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:58:21 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		error(const char *error_str)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(error_str, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}

void	logging(t_philo *philo, const char *str)
{
	sem_wait(philo->table->print);
	printf("%zu %d %s\n",
	(time_unix_seconds() - philo->table->start_table), philo->id, str);
	if (philo->table->death != TRUE)
		sem_post(philo->table->print);
}
