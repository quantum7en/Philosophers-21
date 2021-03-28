/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_in_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:21:45 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:21:47 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		sleep_in_ms(size_t time)
{
	size_t start;
	size_t stop;
	size_t diff;

	start = time_unix_seconds();
	stop = time_unix_seconds();
	diff = stop - start;
	while (diff < time)
	{
		stop = time_unix_seconds();
		diff = stop - start;
		usleep(10);
	}
}
