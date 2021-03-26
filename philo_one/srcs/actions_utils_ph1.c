/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils_ph1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:59:00 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				put_forks(t_philo *ph, int philo_num)
{
	pthread_mutex_unlock(&ph->m_forks[philo_num - 1]);
	pthread_mutex_unlock(&ph->m_forks[right_fork_num(ph, philo_num - 1)]);
	return (0);
}

int				check_philo_status(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(&ph->m_is_philo_dead);
	status = ph->is_philo_dead;
	pthread_mutex_unlock(&ph->m_is_philo_dead);
	return (status);
}

unsigned int	print_status(t_philo *ph, int philo_num, char *action_kind)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(ph);
	pthread_mutex_lock(&ph->m_output_protect);
	if (ph->is_philo_dead == 0)
		printf("%u %d %s\n", timestamp, philo_num, action_kind);
	pthread_mutex_unlock(&ph->m_output_protect);
	return (timestamp);
}

static int		is_time_out(struct timeval *measure_beginning, int action_time)
{
	struct timeval		current_time;
	unsigned long long	time_diff;
	unsigned long long	micro_action_time;

	gettimeofday(&current_time, NULL);
	micro_action_time = action_time * 1000;
	time_diff = current_time.tv_sec * 1000 * 1000 + current_time.tv_usec;
	time_diff -= measure_beginning->tv_sec * 1000 * 1000 +
	measure_beginning->tv_usec;
	return (micro_action_time - time_diff);
}

void			pseudo_usleep(t_philo *ph, int philo_num, int action_time)
{
	int				sleep_left;
	struct timeval	measure_beginning;

	gettimeofday(&measure_beginning, NULL);
	while (get_current_timestamp(ph) - ph->time_of_last_meal
		[philo_num - 1] < ph->params.time_to_die && (sleep_left =
		is_time_out(&measure_beginning, action_time)) > 0)
	{
		if (sleep_left > 10000)
			usleep(10000);
		else if (sleep_left > 100)
			usleep(100);
		else if (sleep_left > 10)
			usleep(10);
		else if (sleep_left > 5)
			usleep(5);
	}
}
