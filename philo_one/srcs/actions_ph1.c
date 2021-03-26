/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_ph1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:00:28 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:59:06 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	pseudo_usleep(ph, philo_num, ph->params.time_to_sleep);
	return (0);
}

static int	take_forks(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
	{
		if (ph->forks_status[philo_num - 1] != philo_num &&
			ph->forks_status[right_fork_num(ph, philo_num - 1)] != philo_num)
		{
			pthread_mutex_lock(&ph->m_forks[philo_num - 1]);
			ph->forks_status[philo_num - 1] = philo_num;
			if (check_philo_status(ph) == 0)
				print_status(ph, philo_num, "has taken a fork");
			pthread_mutex_lock(&ph->m_forks
				[right_fork_num(ph, philo_num - 1)]);
			ph->forks_status[right_fork_num(ph, philo_num - 1)] = philo_num;
			if (check_philo_status(ph) == 0)
				print_status(ph, philo_num, "has taken a fork");
		}
		else
			return (1);
	}
	return (0);
}

static int	eating(t_philo *ph, int philo_num)
{
	if (check_philo_status(ph) == 0)
		ph->time_of_last_meal[philo_num - 1] =
	print_status(ph, philo_num, "is eating");
	else
	{
		put_forks(ph, philo_num);
		return (philo_death(ph, philo_num));
	}
	pseudo_usleep(ph, philo_num, ph->params.time_to_eat);
	put_forks(ph, philo_num);
	return (0);
}

void		*philosopher_routine(void *arg)
{
	t_philo	*ph;
	int		philo_num;
	int		i;

	ph = (t_philo *)arg;
	philo_num = get_philosopher_number(ph);
	i = 0;
	while (1)
	{
		if (take_forks(ph, philo_num) != 0)
			continue ;
		if (eating(ph, philo_num) != 0)
			return (NULL);
		i++;
		if (ph->params.times_must_eat != -1 && ph->params.times_must_eat == i)
			return (philo_is_full(ph));
		if (sleeping(ph, philo_num) != 0)
			return (NULL);
		if (thinking(ph, philo_num) != 0)
			return (NULL);
	}
	return (NULL);
}
