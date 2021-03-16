/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/16 20:04:03 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		thinking(t_all *all, int philo_personal_number)
{
	ssize_t timestamp;

	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is thinking\n", timestamp, philo_personal_number);
	else
		return (philo_death(all, timestamp, philo_personal_number));
	return (0);
}

int		sleeping(t_all *all, int philo_personal_number)
{
	ssize_t timestamp;

	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is sleeping\n", timestamp, philo_personal_number);
	else
		return (philo_death(all, timestamp, philo_personal_number));
	usleep(all->params->time_to_sleep * 1000);
	return (0);
}

int		take_forks(t_all *all, int philo_personal_number)
{
	ssize_t timestamp;

	if (all->is_philo_dead == 0)
	{
		if (all->forks_status[philo_personal_number - 1] != philo_personal_number &&
			all->forks_status[right_fork_num(all, philo_personal_number - 1)] != philo_personal_number)
		{
			timestamp = get_current_timestamp(all);
			pthread_mutex_lock(&all->m_forks[philo_personal_number - 1]);
			all->forks_status[philo_personal_number - 1] = philo_personal_number;
			if (all->is_philo_dead == 0)
				printf("%zd %d has taken a fork\n", timestamp, philo_personal_number);
			pthread_mutex_lock(&all->m_forks[right_fork_num(all, philo_personal_number - 1)]);
			all->forks_status[right_fork_num(all, philo_personal_number - 1)] = philo_personal_number;
			if (all->is_philo_dead == 0)
				printf("%zd %d has taken a fork\n", timestamp, philo_personal_number);
		}
		else
			return (1);
	}
	return (0);
}

int		put_forks(t_all *all, int philo_personal_number)
{
	pthread_mutex_unlock(&all->m_forks[philo_personal_number - 1]);
	pthread_mutex_unlock(&all->m_forks[right_fork_num(all, philo_personal_number - 1)]);
	return (0);
}

int		eating(t_all *all, int philo_personal_number)
{
	ssize_t timestamp;

	
	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is eating\n", timestamp, philo_personal_number);
	else
	{
		put_forks(all, philo_personal_number);
		return (philo_death(all, timestamp, philo_personal_number));
	}
	all->time_of_last_meal[philo_personal_number - 1] = timestamp;
	// timestamp;
	usleep(all->params->time_to_eat * 1000);
	put_forks(all, philo_personal_number);
	return (0);
}
