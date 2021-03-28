/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:25:38 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:37:20 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_atoi(const char *nptr)
{
	size_t				i;
	int					sign;
	unsigned long int	nbr;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] != '\0') && (nptr[i] == ' ' || nptr[i] == '\n' ||
								nptr[i] == '\t' || nptr[i] == '\v' ||
								nptr[i] == '\f' || nptr[i] == '\r'))
		i++;
	if (nptr[i] == '-')
		return (-1);
	if ((nptr[i] == '+') || (nptr[i] == '-'))
		i++;
	while ((nptr[i] != '\0') && ('0' <= nptr[i]) && (nptr[i] <= '9'))
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	return (sign * (int)nbr);
}
