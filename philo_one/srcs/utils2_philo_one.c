/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_philo_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/18 18:38:46 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_philo_status(t_all *all)
{
	int	status;

	pthread_mutex_lock(&all->m_is_philo_dead);
	status = all->is_philo_dead;
	pthread_mutex_unlock(&all->m_is_philo_dead);
	return (status);
}

int		print_status(t_all *all, ssize_t timestamp, int philo_num,
	char *kind_of_action)
{
	pthread_mutex_lock(&all->m_output_protect);
	if (all->is_philo_dead == 0)
		printf("%zd %d %s\n", timestamp, philo_num, kind_of_action);
	pthread_mutex_unlock(&all->m_output_protect);
	return (0);
}

int		is_time_out(struct timeval *measure_beginning, int action_time)
{
	struct timeval 		current_time;
	unsigned long long	time_diff;
	unsigned long long	micro_action_time;

	gettimeofday(&current_time, NULL);
	micro_action_time = action_time * 1000;
	time_diff = current_time.tv_sec * 1000 * 1000 + current_time.tv_usec;
	time_diff -= measure_beginning->tv_sec * 1000 * 1000 +
	measure_beginning->tv_usec;
	return (time_diff >= micro_action_time);
}

int		pseudo_usleep(t_all *all, int action_time)
{
	int i;

	i = 0;
	struct timeval	measure_beginning;

	gettimeofday(&measure_beginning, NULL);
	usleep(action_time * (975));// - all->params.amount_of_philosophers / 4));
	while (!is_time_out(&measure_beginning, action_time))
	{
		i++;
		usleep(10);
	}
	dprintf(2, "i = %d\n", i);
	return (0);
}