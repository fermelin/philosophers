/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_ph1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/23 19:16:02 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	thinking(t_all *all, int philo_num)
{
	if (check_philo_status(all) == 0)
		print_status(all, philo_num, "is thinking");
	else
		return (philo_death(all, philo_num));
	return (0);
}

static int	sleeping(t_all *all, int philo_num)
{
	if (check_philo_status(all) == 0)
		print_status(all, philo_num, "is sleeping");
	else
		return (philo_death(all, philo_num));
	pseudo_usleep(all, philo_num, all->params.time_to_sleep);
	return (0);
}

static int	take_forks(t_all *all, int philo_num)
{
	if (check_philo_status(all) == 0)
	{
		if (all->forks_status[philo_num - 1] != philo_num &&
			all->forks_status[right_fork_num(all, philo_num - 1)] != philo_num)
		{
			pthread_mutex_lock(&all->m_forks[philo_num - 1]);
			all->forks_status[philo_num - 1] = philo_num;
			if (check_philo_status(all) == 0)
				print_status(all, philo_num, "has taken a fork");
			pthread_mutex_lock(&all->m_forks
				[right_fork_num(all, philo_num - 1)]);
			all->forks_status[right_fork_num(all, philo_num - 1)] = philo_num;
			if (check_philo_status(all) == 0)
				print_status(all, philo_num, "has taken a fork");
		}
		else
			return (1);
	}
	return (0);
}

static int	eating(t_all *all, int philo_num)
{
	if (check_philo_status(all) == 0)
		all->time_of_last_meal[philo_num - 1] =
	print_status(all, philo_num, "is eating");
	else
	{
		put_forks(all, philo_num);
		return (philo_death(all, philo_num));
	}
	pseudo_usleep(all, philo_num, all->params.time_to_eat);
	put_forks(all, philo_num);
	return (0);
}

void		*philosopher_routine(void *arg)
{
	t_all	*all;
	int		philo_num;
	int		i;

	all = (t_all *)arg;
	philo_num = get_philosopher_number(all);
	i = 0;
	while (1)
	{
		if (take_forks(all, philo_num) != 0)
			continue ;
		if (eating(all, philo_num) != 0)
			return (NULL);
		i++;
		if (all->params.times_must_eat != -1 && all->params.times_must_eat == i)
			return (philo_is_full(all));
		if (sleeping(all, philo_num) != 0)
			return (NULL);
		if (thinking(all, philo_num) != 0)
			return (NULL);
	}
	return (NULL);
}
