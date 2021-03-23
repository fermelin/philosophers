/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:03:49 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/23 12:43:05 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				ft_atoi(const char *nbr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nbr[i] >= '\t' && nbr[i] <= '\r') || nbr[i] == ' ')
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		sign = (nbr[i] == '-') ? -1 : 1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		if ((res * 10 + (nbr[i] - '0')) < res)
			return ((sign > 0) ? -1 : 0);
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}

int				free_all(t_all *all, int error_number)
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
		printf("%u %d died\n", timestamp, philo_num);
		kill(0, SIGINT);
		sem_post(all->s_is_philo_dead);
	}
	return (1);
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
