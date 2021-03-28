/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:01:41 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:35:08 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		is_exit(t_philo *philo)
{
	if (philo->table->death == TRUE)
		return (TRUE);
	return (FALSE);
}

int		is_philo_die(t_philo *philo)
{
	sem_wait(philo->table->last_eat_mutex);
	if (time_unix_seconds() - philo->last_eat > philo->table->time_life &&
	philo->eating_count != philo->table->num_count_eat)
	{
		philo->table->death = TRUE;
		logging(philo, "died");
		sem_post(philo->table->last_eat_mutex);
		return (TRUE);
	}
	sem_post(philo->table->last_eat_mutex);
	return (FALSE);
}
