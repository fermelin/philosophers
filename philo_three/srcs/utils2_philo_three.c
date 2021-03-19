/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_philo_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/19 12:12:30 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		free_all(t_all *all, int error_number)
{
	if (error_number == JUST_FREE_ALL)
	{
		sem_close(all->s_forks);
		sem_close(all->s_is_philo_dead);
		sem_close(all->s_output_protect);
		sem_unlink("s_forks");
		sem_unlink("s_is_philo_dead");
		sem_unlink("s_output_protect");
	}
	if (error_number == E_MALLOC)
		printf("%s\n", E_MALLOC_TXT);
	return (error_number);
}

int		check_philo_status(t_all *all)
{
	int	status;

	sem_wait(all->s_is_philo_dead);
	status = all->is_philo_dead;
	sem_post(all->s_is_philo_dead);
	return (status);
}

int		print_status(t_all *all, ssize_t timestamp, int philo_num,
	char *kind_of_action)
{
	sem_wait(all->s_output_protect);
	if (all->is_philo_dead == 0)
		printf("%zd %d %s\n", timestamp, philo_num, kind_of_action);
	sem_post(all->s_output_protect);
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
		if (time_to_sleep > 1000)
			usleep(1000);
		else if (time_to_sleep > 100)
			usleep(100);
		else if (time_to_sleep > 10)
			usleep(10);
		else
			usleep(5);
	}
	return (0);
}
