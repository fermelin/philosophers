/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:03:49 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/19 11:49:35 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int				right_fork_num(t_all *all, int philo_index)
{
	return ((philo_index + 1) % all->params.amount_of_philosophers);
}

int				philo_death(t_all *all, ssize_t timestamp, int philo_num)
{
	if (check_philo_status(all) == 0)
	{
		sem_wait(all->s_is_philo_dead);
		all->is_philo_dead = 1;
		sem_post(all->s_is_philo_dead);
		printf("%zd %d died\n", timestamp, philo_num);
	}
	return (1);
}

unsigned int	get_current_timestamp(t_all *all)
{
	struct timeval	current_time;
	unsigned int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	return (timestamp);
}
