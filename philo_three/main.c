/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:58:44 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:47:47 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	parse_table(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (error("Wrong number of args. Number of args should be 4 or 5"));
	memset(table, 0, sizeof(t_table));
	table->num_philo = ft_atoi(argv[1]);
	table->time_life = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if ((table->num_count_eat = ft_atoi(argv[5])) <= 0)
			return (error("num count eat"));
		table->flag_eat_required_times = TRUE;
	}
	if (argc == 5)
		table->num_count_eat = -1;
	if (table->num_philo <= 0 || table->time_life <= 0 ||
	table->time_eat <= 0 || table->time_sleep <= 0)
		return (error("argument number is incorrect"));
	if (table->num_philo > 200 || table->time_life < 60 ||
	table->time_eat < 60 || table->time_sleep < 60)
		return (error("don't test with more than 200 philos or time under 60"));
	return (SUCCESS);
}

static int	init_philos(t_table *table, t_philo **philos)
{
	int i;

	i = -1;
	sem_unlink("/fork_sem");
	sem_unlink("/last_eat");
	sem_unlink("/print_sem");
	sem_unlink("/waiter");
	if (((table->forks =
	sem_open("/fork_sem", O_CREAT, S_IRWXU, table->num_philo)) == SEM_FAILED)
	|| ((table->print =
	sem_open("/print_sem", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
	|| ((table->last_eat_mutex =
	sem_open("/last_eat", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
	|| ((table->waiter =
	sem_open("/waiter", O_CREAT, S_IRWXU, 1)) == SEM_FAILED))
		return (error("Semaphore init"));
	if (!(*philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philo)))
		return (error("malloc all philos"));
	table->count_full_philos = 0;
	while (++i < table->num_philo - 1)
		(*philos)[i] = (t_philo){i + 1, 0, time_unix_seconds(), FALSE,
							table, 0, NULL};
	(*philos)[table->num_philo - 1] =
	(t_philo){table->num_philo, 0, time_unix_seconds(), FALSE, table, 0, NULL};
	return (SUCCESS);
}

int			setup_threads(pthread_t **threads, t_philo *philos, t_table *table)
{
	pthread_t	*tmp_threads;
	int			i;

	i = 0;
	if (!(tmp_threads =
	(pthread_t *)malloc(sizeof(pthread_t) * table->num_philo)))
		return (error("malloc"));
	while (i < table->num_philo)
	{
		if (pthread_create(&tmp_threads[i], NULL, philo_life_new, &philos[i]))
			return (error("pthread create odd philos "));
		pthread_detach(tmp_threads[i]);
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < table->num_philo)
	{
		if (pthread_create(&tmp_threads[i], NULL, philo_life_new, &philos[i]))
			return (error("pthread create even philos "));
		pthread_detach(tmp_threads[i]);
		i += 2;
	}
	*threads = tmp_threads;
	return (SUCCESS);
}

int			run_philos(t_table *table, t_philo *philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	table->start_table = time_unix_seconds();
	if (!(setup_threads(&threads, philos, table)))
		return (error("setup threads"));
	while (table->count_full_philos != table->num_philo)
	{
		if (table->death)
			break ;
		i = (i + 1) % table->num_philo;
	}
	free(threads);
	return (SUCCESS);
}

int			main(int argc, char *argv[])
{
	t_table		table;
	t_philo		*philos;

	if (!(parse_table(argc, argv, &table)))
		return (error("parse check params"));
	if (!init_philos(&table, &philos))
		return (error("init philos"));
	if (!(run_philos(&table, philos)))
		return (error("run philos"));
	if (philos)
		free(philos);
	usleep(50000);
	return (0);
}
