/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_ph3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:58:11 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	thinking(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
		print_status(ph, philo_num, "is thinking");
	else
		return (philo_death(ph, philo_num));
	return (0);
}

static int	sleeping(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
		print_status(ph, philo_num, "is sleeping");
	else
		return (philo_death(ph, philo_num));
	pseudo_usleep(ph, ph->params.time_to_sleep);
	return (0);
}

static int	take_forks(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
	{
		sem_wait(ph->s_forks);
		sem_wait(ph->s_forks);
		if (check_philo_status(ph) == 0)
		{
			print_status(ph, philo_num, "has taken a fork");
			print_status(ph, philo_num, "has taken a fork");
		}
	}
	else
		return (1);
	return (0);
}

static int	eating(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
		ph->time_of_last_meal = print_status(ph, philo_num, "is eating");
	else
	{
		put_forks(ph);
		return (philo_death(ph, philo_num));
	}
	pseudo_usleep(ph, ph->params.time_to_eat);
	put_forks(ph);
	return (0);
}

void		philosopher_routine(t_philo ph, int philo_num)
{
	int		i;

	i = 0;
	pthread_create(&ph.thread_id, NULL,
	&death_checking, &ph);
	pthread_detach(ph.thread_id);
	while (1)
	{
		if (take_forks(&ph, philo_num) != 0)
			continue ;
		if (eating(&ph, philo_num) != 0)
			exit(1);
		i++;
		if (ph.params.times_must_eat != -1 && ph.params.times_must_eat == i)
			exit(0);
		if (sleeping(&ph, philo_num) != 0)
			exit(1);
		if (thinking(&ph, philo_num) != 0)
			exit(1);
	}
}
