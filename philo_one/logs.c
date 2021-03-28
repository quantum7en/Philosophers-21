/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:20:58 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:21:36 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		error(const char *error_str)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(error_str, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}

void	logging(t_philo *philo, const char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%zu %d %s\n", (time_unix_seconds() - \
	philo->table->start_table), philo->id, str);
	pthread_mutex_unlock(philo->print_mutex);
}
