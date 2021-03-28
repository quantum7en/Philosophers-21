/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:02:46 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:47:44 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	logging(philo, "has taken a fork");
	if (is_philo_die(philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	logging(philo, "has taken a fork");
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = time_unix_seconds();
	pthread_mutex_unlock(philo->last_eat_mutex);
	logging(philo, "is eating");
	if (sleep_in_ms(philo->table->time_eat, philo))
		return (1);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static int		sleep_and_think(t_philo *philo)
{
	logging(philo, "is sleeping");
	if (sleep_in_ms(philo->table->time_sleep, philo))
	{
		philo->table->death = TRUE;
		pthread_mutex_lock(philo->print_mutex);
		return (1);
	}
	logging(philo, "is thinking");
	return (0);
}

static int		living(t_philo *philo)
{
	if (eat(philo))
	{
		philo->table->death = TRUE;
		pthread_mutex_lock(philo->print_mutex);
		return (1);
	}
	philo->eating_count++;
	if (philo->table->flag_eat_required_times == TRUE)
		if (philo->eating_count == philo->table->num_count_eat)
		{
			philo->table->count_full_philos++;
			return (1);
		}
	if (sleep_and_think(philo))
		return (1);
	return (0);
}

void			*philo_life_new(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = time_unix_seconds();
	pthread_mutex_unlock(philo->last_eat_mutex);
	philo->eating_count = 0;
	while (TRUE)
	{
		if (!(is_philo_die(philo)))
		{
			if (living(philo))
				break ;
		}
		else
		{
			philo->table->death = TRUE;
			pthread_mutex_lock(philo->print_mutex);
			break ;
		}
	}
	return (0x000);
}
