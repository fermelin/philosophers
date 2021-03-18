/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_philo_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/18 21:08:53 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		free_all(t_all *all, int error_number)
{
	int i;

	if (error_number == JUST_FREE_ALL)
	{
		i = 0;
		while (i < all->params.amount_of_philosophers)
			if (pthread_mutex_destroy(&all->m_forks[i++]) != 0)
				printf("mutex_destroy error\n");
		pthread_mutex_destroy(&all->mutex_for_getting_philo_number);
		pthread_mutex_destroy(&all->m_is_philo_dead);
		pthread_mutex_destroy(&all->m_output_protect);
	}
	free(all->m_forks);
	free(all->time_of_last_meal);
	free(all->forks_status);
	free(all->thread_id);
	if (error_number == E_MALLOC)
		printf("%s\n", E_MALLOC_TXT);
	return (error_number);
}

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

int		pseudo_usleep(int action_time)
{
	int				time_to_sleep;
	struct timeval	measure_beginning;

	gettimeofday(&measure_beginning, NULL);
	usleep(action_time * (974));
	while ((time_to_sleep = is_time_out(&measure_beginning, action_time)) > 0)
	{
		if (time_to_sleep > 100)
			usleep(100);
		else if (time_to_sleep > 10)
			usleep(10);
		else
			usleep(5);
	}
	return (0);
}
