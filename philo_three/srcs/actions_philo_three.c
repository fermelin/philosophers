/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/19 12:13:38 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		thinking(t_all *all, int philo_num)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp - all->time_of_last_meal <=
		all->params.time_to_die)
		print_status(all, timestamp, philo_num, "is thinking");
	else
		return (philo_death(all, timestamp, philo_num));
	return (0);
}

int		sleeping(t_all *all, int philo_num)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp - all->time_of_last_meal <=
		all->params.time_to_die)
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
		timestamp = get_current_timestamp(all);
		sem_wait(all->s_forks);
		sem_wait(all->s_forks);
		if (check_philo_status(all) == 0)
		{
			print_status(all, timestamp, philo_num, "has taken a fork");
			print_status(all, timestamp, philo_num, "has taken a fork");
		}
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
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	if (check_philo_status(all) == 0 && timestamp -
		all->time_of_last_meal <= all->params.time_to_die)
		print_status(all, timestamp, philo_num, "is eating");
	else
	{
		put_forks(all);
		return (philo_death(all, timestamp, philo_num));
	}
	all->time_of_last_meal = timestamp;
	pseudo_usleep(all->params.time_to_eat);
	put_forks(all);
	return (0);
}
