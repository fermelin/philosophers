/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:03:49 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/22 23:05:55 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				free_all(t_all *all, int error_number)
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

int				right_fork_num(t_all *all, int philo_index)
{
	return ((philo_index + 1) % all->params.amount_of_philosophers);
}

int				philo_death(t_all *all, int philo_num)
{
	unsigned int	timestamp;

	if (check_philo_status(all) == 0)
	{
		timestamp = get_current_timestamp(all);
		pthread_mutex_lock(&all->m_is_philo_dead);
		all->is_philo_dead = 1;
		pthread_mutex_unlock(&all->m_is_philo_dead);
		printf("%u %d died\n", timestamp, philo_num);
	}
	return (1);
}

int				get_philosopher_number(t_all *all)
{
	int		tmp_philo_number;

	pthread_mutex_lock(&all->mutex_for_getting_philo_number);
	all->tmp_philo_num++;
	tmp_philo_number = all->tmp_philo_num;
	pthread_mutex_unlock(&all->mutex_for_getting_philo_number);
	return (tmp_philo_number);
}

unsigned int	get_current_timestamp(t_all *all)
{
	struct timeval	current_time;
	unsigned int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	return (timestamp);
}
