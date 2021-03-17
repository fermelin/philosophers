/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:03:49 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 18:45:11 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_atoi(const char *nbr)
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

int		right_fork_num(t_all *all, int philo_index)
{
	return ((philo_index + 1) % all->params.amount_of_philosophers);
}

int		philo_death(t_all *all, ssize_t timestamp, int philo_num)
{
	if (all->is_philo_dead == 0)
	{
		all->is_philo_dead = 1;
		printf("%zd %d died\n", timestamp, philo_num);
	}
	return (1);
}

int		get_philosopher_number(t_all *all)
{
	int		tmp_philo_number;

	printf("sem before= %d\n", *(all->sem_for_getting_philo_number));
	sem_wait(all->sem_for_getting_philo_number);
	printf("sem after= %d\n", *(all->sem_for_getting_philo_number));
	all->tmp_philo_num++;
	tmp_philo_number = all->tmp_philo_num;
	sem_post(all->sem_for_getting_philo_number);
	return (tmp_philo_number);
}

ssize_t	get_current_timestamp(t_all *all)
{
	struct timeval	current_time;
	ssize_t			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	return (timestamp);
}