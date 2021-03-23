/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils_ph3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/23 12:42:54 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				put_forks(t_all *all)
{
	sem_post(all->s_forks);
	sem_post(all->s_forks);
	return (0);
}

int				check_philo_status(t_all *all)
{
	int	status;

	sem_wait(all->s_is_philo_dead);
	status = all->is_philo_dead;
	sem_post(all->s_is_philo_dead);
	return (status);
}

unsigned int	print_status(t_all *all, int philo_num, char *action_kind)
{
	unsigned int timestamp;

	timestamp = get_current_timestamp(all);
	sem_wait(all->s_output_protect);
	if (all->is_philo_dead == 0)
		printf("%u %d %s\n", timestamp, philo_num, action_kind);
	sem_post(all->s_output_protect);
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

void			pseudo_usleep(t_all *all, int action_time)
{
	int				sleep_left;
	struct timeval	measure_beginning;

	gettimeofday(&measure_beginning, NULL);
	while (get_current_timestamp(all) - all->time_of_last_meal
		< all->params.time_to_die && (sleep_left =
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
