/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:03:49 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/22 23:34:51 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				free_all(t_all *all, int error_number)
{
	if (error_number == JUST_FREE_ALL)
	{
		sem_close(all->s_for_getting_philo_number);
		sem_close(all->s_forks);
		sem_close(all->s_is_philo_dead);
		sem_close(all->s_output_protect);
		sem_unlink("s_for_getting_philo_number");
		sem_unlink("s_forks");
		sem_unlink("s_is_philo_dead");
		sem_unlink("s_output_protect");
	}
	free(all->time_of_last_meal);
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
		sem_wait(all->s_is_philo_dead);
		all->is_philo_dead = 1;
		sem_post(all->s_is_philo_dead);
		printf("%u %d died\n", timestamp, philo_num);
	}
	return (1);
}

int				get_philosopher_number(t_all *all)
{
	int		tmp_philo_number;

	sem_wait(all->s_for_getting_philo_number);
	all->tmp_philo_num++;
	tmp_philo_number = all->tmp_philo_num;
	sem_post(all->s_for_getting_philo_number);
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
