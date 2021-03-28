/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_unix_seconds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:50:32 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:51:10 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	time_unix_seconds(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + ((long int)s_time.tv_usec / 1000));
}
