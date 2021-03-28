/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:51:52 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:23:08 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	mutexes_init2(pthread_mutex_t **die_mutex, \
pthread_mutex_t **last_eat_mutex, \
pthread_mutex_t **print_mutex)
{
	pthread_mutex_t	*tmp_die_mutex;
	pthread_mutex_t	*tmp_last_eat_mutex;
	pthread_mutex_t	*tmp_print_mutex;

	if (!(tmp_die_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return (error("malloc die"));
	if (!(tmp_print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return (error("malloc print"));
	if (!(tmp_last_eat_mutex = \
	(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return (error("malloc last eat"));
	if (pthread_mutex_init(tmp_die_mutex, NULL) ||
		pthread_mutex_init(tmp_print_mutex, NULL) ||
		pthread_mutex_init(tmp_last_eat_mutex, NULL))
		return (error("mutex init"));
	*print_mutex = tmp_print_mutex;
	*last_eat_mutex = tmp_last_eat_mutex;
	*die_mutex = tmp_die_mutex;
	return (SUCCESS);
}

static int	mutexes_init(pthread_mutex_t **forks_mutexes)
{
	pthread_mutex_t	*tmp_forks;
	int				i;

	i = -1;
	if (!(tmp_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	g_num_philo)))
		return (error("malloc forks"));
	while (++i < g_num_philo)
		if (pthread_mutex_init(&(tmp_forks[i]), NULL))
			return (error("mutex init"));
	*forks_mutexes = tmp_forks;
	return (SUCCESS);
}

int			init_philos(t_table *table, t_philo **philos, t_garbage *garbage)
{
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*print_mutex;
	int				i;

	i = -1;
	if (!(mutexes_init(&forks_mutexes)) || \
	!(mutexes_init2(&die_mutex, &last_eat_mutex, &print_mutex)))
		return (error("mutexes init"));
	if (!(*philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philo)))
		return (error("malloc all philos"));
	table->count_full_philos = 0;
	while (++i < table->num_philo - 1)
		(*philos)[i] = (t_philo){i + 1, time_unix_seconds(),
						&(forks_mutexes[i]), &(forks_mutexes[i + 1]),
						die_mutex, last_eat_mutex, print_mutex, table, 0};
	(*philos)[table->num_philo - 1] =
					(t_philo){table->num_philo, time_unix_seconds(),
					&(forks_mutexes[table->num_philo - 1]), &(forks_mutexes[0]),
					die_mutex, last_eat_mutex, print_mutex, table, 0};
	*garbage =
	(t_garbage){forks_mutexes, last_eat_mutex, die_mutex, print_mutex};
	return (SUCCESS);
}

int			setup_threads(pthread_t **threads, t_philo *philos, t_table *table)
{
	pthread_t	*tmp_threads;
	int			i;

	i = -1;
	if (!(tmp_threads =
	(pthread_t *)malloc(sizeof(pthread_t) * table->num_philo)))
		return (error("malloc"));
	while (++i < table->num_philo)
	{
		philos[i].last_eat = time_unix_seconds();
		if (pthread_create(&tmp_threads[i], NULL, philo_life_new, &philos[i]))
			return (error("pthread create odd philos "));
		pthread_detach(tmp_threads[i]);
		usleep(250);
	}
	*threads = tmp_threads;
	return (SUCCESS);
}
