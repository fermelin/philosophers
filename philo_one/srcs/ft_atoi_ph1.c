/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ph1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:53:22 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/22 23:05:10 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_atoi(const char *nbr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nbr[i] >= '\t' && nbr[i] <= '\r') || nbr[i] == ' ')
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		sign = (nbr[i] == '-') ? -1 : 1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		if ((res * 10 + (nbr[i] - '0')) < res)
			return ((sign > 0) ? -1 : 0);
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}