/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_in_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:29:50 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:29:58 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		sleep_in_ms(size_t time, t_philo *philo)
{
	size_t start;
	size_t stop;
	size_t diff;

	start = time_unix_seconds();
	stop = time_unix_seconds();
	diff = stop - start;
	while (diff < time)
	{
		if (is_philo_die(philo))
			return (1);
		stop = time_unix_seconds();
		diff = stop - start;
		usleep(10);
	}
	return (0);
}
