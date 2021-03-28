/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:01:41 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:29:18 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		is_philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->last_eat_mutex);
	if (time_unix_seconds() - philo->last_eat > philo->table->time_life &&
	philo->eating_count != philo->table->num_count_eat)
	{
		philo->table->death = TRUE;
		logging(philo, "died");
		pthread_mutex_lock(philo->print_mutex);
		pthread_mutex_unlock(philo->last_eat_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->last_eat_mutex);
	return (FALSE);
}
