/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/18 22:15:39 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		thinking(t_all *all, int philo_num)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp - all->time_of_last_meal
		[philo_num - 1] <= all->params.time_to_die)
		print_status(all, timestamp, philo_num, "is thinking");
	else
		return (philo_death(all, timestamp, philo_num));
	return (0);
}

int		sleeping(t_all *all, int philo_num)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp - all->time_of_last_meal
		[philo_num - 1] <= all->params.time_to_die)
		print_status(all, timestamp, philo_num, "is sleeping");
	else
		return (philo_death(all, timestamp, philo_num));
	pseudo_usleep(all->params.time_to_sleep);
	return (0);
}

int		take_forks(t_all *all, int philo_num)
{
	unsigned int timestamp;

	if (check_philo_status(all) == 0)
	{
		if (all->forks_status[philo_num - 1] != philo_num &&
			all->forks_status[right_fork_num(all, philo_num - 1)] != philo_num)
		{
			timestamp = get_current_timestamp(all);
			pthread_mutex_lock(&all->m_forks[philo_num - 1]);
			all->forks_status[philo_num - 1] = philo_num;
			if (check_philo_status(all) == 0)
				print_status(all, timestamp, philo_num, "has taken a fork");
			pthread_mutex_lock(&all->m_forks
				[right_fork_num(all, philo_num - 1)]);
			all->forks_status[right_fork_num(all, philo_num - 1)] = philo_num;
			if (check_philo_status(all) == 0)
				print_status(all, timestamp, philo_num, "has taken a fork");
		}
		else
			return (1);
	}
	return (0);
}

int		put_forks(t_all *all, int philo_num)
{
	pthread_mutex_unlock(&all->m_forks[philo_num - 1]);
	pthread_mutex_unlock(&all->m_forks[right_fork_num(all, philo_num - 1)]);
	return (0);
}

int		eating(t_all *all, int philo_num)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp -
		all->time_of_last_meal[philo_num - 1] <= all->params.time_to_die)
		print_status(all, timestamp, philo_num, "is eating");
	else
	{
		put_forks(all, philo_num);
		return (philo_death(all, timestamp, philo_num));
	}
	all->time_of_last_meal[philo_num - 1] = timestamp;
	pseudo_usleep(all->params.time_to_eat);
	put_forks(all, philo_num);
	return (0);
}
