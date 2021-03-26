/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils_ph2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 13:57:26 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				put_forks(t_philo *ph)
{
	sem_post(ph->s_forks);
	sem_post(ph->s_forks);
	return (0);
}

int				check_philo_status(t_philo *ph)
{
	int	status;

	sem_wait(ph->s_is_philo_dead);
	status = ph->is_philo_dead;
	sem_post(ph->s_is_philo_dead);
	return (status);
}

int				print_status(t_philo *ph, int philo_num, char *action_kind)
{
	unsigned int timestamp;

	if (check_philo_status(ph) == 0)
	{
		timestamp = get_current_timestamp(ph);
		sem_wait(ph->s_output_protect);
		if (ph->is_philo_dead == 0)
			printf("%u %d %s\n", timestamp, philo_num, action_kind);
		sem_post(ph->s_output_protect);
		return (0);
	}
	else
		return (1);
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
		else if (sleep_left > 1000)
			usleep(1000);
		else if (sleep_left > 100)
			usleep(100);
		else if (sleep_left > 10)
			usleep(10);
		else if (sleep_left > 5)
			usleep(5);
	}
}
