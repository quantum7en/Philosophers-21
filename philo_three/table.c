/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:02:46 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:46:20 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		*check_death(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (TRUE)
	{
		if (is_philo_die(philo))
		{
			philo->table->death = TRUE;
			sem_wait(philo->table->print);
			exit(1);
		}
		usleep(100);
	}
	return (0x00);
}

static void		eat(t_philo *philo)
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

static int		daughter(t_philo *philo)
{
	pthread_t	daughter_thread;

	philo->daughter_thread = &daughter_thread;
	pthread_create(philo->daughter_thread, NULL, check_death, (void *)philo);
	while (TRUE)
	{
		eat(philo);
		philo->eating_count++;
		if (philo->table->flag_eat_required_times == TRUE)
			if (philo->eating_count == philo->table->num_count_eat)
			{
				philo->table->count_full_philos++;
				return (2);
			}
		logging(philo, "is sleeping");
		if (sleep_in_ms(philo->table->time_sleep))
			return (1);
		logging(philo, "is thinking");
	}
	pthread_detach(daughter_thread);
	return (1);
}

void			*philo_life_new(void *data)
{
	t_philo		*philo;
	int			res;
	pid_t		pid;

	philo = (t_philo *)data;
	sem_wait(philo->table->last_eat_mutex);
	philo->last_eat = time_unix_seconds();
	sem_post(philo->table->last_eat_mutex);
	philo->eating_count = 0;
	if (!(pid = fork()))
		exit(daughter(philo));
	waitpid(pid, &res, 0);
	if (WEXITSTATUS(res) == 2)
		philo->table->count_full_philos++;
	if (WEXITSTATUS(res) == 1)
		philo->table->death = 1;
	return (0x000);
}
