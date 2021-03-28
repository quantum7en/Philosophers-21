/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:26:54 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:27:03 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_putstr_fd(const char *s, int fd)
{
	if (s && *s)
		write(fd, s, ft_strlen(s));
}