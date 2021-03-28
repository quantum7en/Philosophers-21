/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_unix_seconds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:23:54 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:24:02 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t	time_unix_seconds(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + ((long int)s_time.tv_usec / 1000));
}
