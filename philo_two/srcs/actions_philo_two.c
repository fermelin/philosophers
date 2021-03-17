/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 18:35:23 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		thinking(t_all *all, int philo_num)
{
	ssize_t timestamp;

	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal
		[philo_num - 1] <= all->params.time_to_die)
		printf("%zd %d is thinking\n", timestamp, philo_num);
	else
		return (philo_death(all, timestamp, philo_num));
	return (0);
}

int		sleeping(t_all *all, int philo_num)
{
	ssize_t timestamp;

	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal
		[philo_num - 1] <= all->params.time_to_die)
		printf("%zd %d is sleeping\n", timestamp, philo_num);
	else
		return (philo_death(all, timestamp, philo_num));
	usleep(all->params.time_to_sleep * 1000);
	return (0);
}

int		take_forks(t_all *all, int philo_num)
{
	ssize_t timestamp;

	if (all->is_philo_dead == 0)
	{
		timestamp = get_current_timestamp(all);
		sem_wait(all->s_forks);
		if (all->is_philo_dead == 0)
			printf("%zd %d has taken a fork\n", timestamp, philo_num);
		sem_wait(all->s_forks);
		if (all->is_philo_dead == 0)
			printf("%zd %d has taken a fork\n", timestamp, philo_num);
	}
	else
		return (1);
	return (0);
}

int		put_forks(t_all *all)
{
	sem_post(all->s_forks);
	sem_post(all->s_forks);
	return (0);
}

int		eating(t_all *all, int philo_num)
{
	ssize_t timestamp;

	timestamp = get_current_timestamp(all);
	if (all->is_philo_dead == 0 && timestamp -
		all->time_of_last_meal[philo_num - 1] <= all->params.time_to_die)
		printf("%zd %d is eating\n", timestamp, philo_num);
	else
	{
		put_forks(all);
		return (philo_death(all, timestamp, philo_num));
	}
	all->time_of_last_meal[philo_num - 1] = timestamp;
	usleep(all->params.time_to_eat * 1000);
	put_forks(all);
	return (0);
}
