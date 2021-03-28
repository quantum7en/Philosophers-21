/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:02:46 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:23:22 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			eat(t_philo *philo)
{
	sem_wait(philo->table->waiter);
	sem_wait(philo->table->forks);
	sem_wait(philo->table->forks);
	sem_post(philo->table->waiter);
	logging(philo, "has taken a fork");
	logging(philo, "has taken a fork");
	sem_wait(philo->table->last_eat_mutex);
	philo->last_eat = time_unix_seconds();
	sem_post(philo->table->last_eat_mutex);
	logging(philo, "is eating");
	sleep_in_ms(philo->table->time_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void			*philo_life_new(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	sem_wait(philo->table->last_eat_mutex);
	philo->last_eat = time_unix_seconds();
	sem_post(philo->table->last_eat_mutex);
	philo->eating_count = 0;
	while (TRUE)
	{
		eat(philo);
		philo->eating_count++;
		if (philo->table->flag_eat_required_times == TRUE)
			if (philo->eating_count == philo->table->num_count_eat)
			{
				philo->table->count_full_philos++;
				return (NULL);
			}
		logging(philo, "is sleeping");
		sleep_in_ms(philo->table->time_sleep);
		logging(philo, "is thinking");
	}
	return (0x000);
}
