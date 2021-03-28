/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:58:44 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:27:00 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "philo_one.h"

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
	if (table->num_philo < 2 || table->time_life <= 0 ||
	table->time_eat <= 0 || table->time_sleep <= 0)
		return (error("argument number is incorrect"));
	if (table->num_philo > 200 || table->time_life < 60 ||
	table->time_eat < 60 || table->time_sleep < 60)
		return (error("don't test with more than 200 philos or time under 60"));
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
	table->threads = threads;
	while (table->count_full_philos != table->num_philo)
	{
		if (is_philo_die(&philos[i]) || table->death == TRUE)
			break ;
		i = (i + 1) % table->num_philo;
	}
	usleep(500000);
	free(threads);
	return (SUCCESS);
}

int			main(int argc, char *argv[])
{
	t_table		table;
	t_philo		*philos;
	t_garbage	garbage;

	g_num_philo = 0;
	table.death = FALSE;
	if (!(parse_table(argc, argv, &table)))
		return (error("parse check params"));
	g_num_philo = table.num_philo;
	if (!init_philos(&table, &philos, &garbage))
		return (error("init philos"));
	if (!(run_philos(&table, philos)))
		return (error("run philos"));
	if (philos)
		free(philos);
	free(garbage.print_mutex);
	free(garbage.last_eat_mutex);
	free(garbage.forks);
	free(garbage.die_mutex);
	return (0);
}
