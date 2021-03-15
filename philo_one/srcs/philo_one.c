/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/15 19:39:01 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		error_processing(int error_number)
{
	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_INIT)
		printf("%s\n", E_INIT_TXT);
	return (error_number);
}

int		init_all_params(t_all *all, t_params *params, char **argv, int argc)
{
	int		i;

	params->amount_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	all->tmp_philo_personal_number = 0;
	all->is_philo_dead = 0;
	if (argc == 6)
		params->times_must_eat = ft_atoi(argv[5]);
	else
		params->times_must_eat = -1;
	if (!(all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* params->amount_of_philosophers)))
		return (1);
	if (!(all->time_of_last_meal = (ssize_t *)malloc(sizeof(ssize_t)
		* params->amount_of_philosophers)))
		return (1);
	i = 0;
	while (i < params->amount_of_philosophers)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		all->time_of_last_meal[i] = 0;
		i++;
	}
	pthread_mutex_init(&all->mutex_for_getting_philo_number, NULL);
	memset(all->forks, 0, (sizeof(int) * params->amount_of_philosophers));
	if (!(all->thread_id =(pthread_t *)malloc(sizeof(pthread_t)
		* params->amount_of_philosophers)))
		return (1);
	gettimeofday(&all->initial_time, NULL);
	return (0);
}

int		philo_death(t_all *all, ssize_t timestamp, int philo_personal_number)
{
	if (all->is_philo_dead == 0)
	{
		all->is_philo_dead = 1;
		printf("%zd %d died\n", timestamp, philo_personal_number);
	}
	return (1);
}

int		thinking(t_all *all, int philo_personal_number)
{
	struct timeval current_time;
	ssize_t timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is thinking\n", timestamp, philo_personal_number);
	else
		return (philo_death(all, timestamp, philo_personal_number));
	return (0);
}

int		sleeping(t_all *all, int philo_personal_number)
{
	struct timeval current_time;
	ssize_t timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is sleeping\n", timestamp, philo_personal_number);
	else
		return (philo_death(all, timestamp, philo_personal_number));
	usleep(all->params->time_to_sleep * 1000);
	return (0);
}

int		eating(t_all *all, int philo_personal_number)
{
	struct timeval current_time;

	ssize_t timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - all->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - all->initial_time.tv_usec) / 1000;
	if (all->is_philo_dead == 0 && timestamp - all->time_of_last_meal[philo_personal_number - 1] < all->params->time_to_die)
		printf("%zd %d is eating\n", timestamp, philo_personal_number);
	else
		return (philo_death(all, timestamp, philo_personal_number));
	all->time_of_last_meal[philo_personal_number - 1] = timestamp;
	usleep(all->params->time_to_eat * 1000);
	return (0);
}

int		get_philosopher_number(t_all *all)
{
	int		tmp_philo_number;

	pthread_mutex_lock(&all->mutex_for_getting_philo_number);
	all->tmp_philo_personal_number++;
	tmp_philo_number = all->tmp_philo_personal_number;
	pthread_mutex_unlock(&all->mutex_for_getting_philo_number);
	return (tmp_philo_number);
}

void	*philosopher_routine(void *arg)
{
	t_all	*all;
	int		philo_personal_number;

	all = (t_all *)arg;
	philo_personal_number = get_philosopher_number(all);
	printf("philo number is %d\n", philo_personal_number);
	while (1)
	{
		if (eating(all, philo_personal_number) != 0)
			return (NULL);
		if (sleeping(all, philo_personal_number) != 0)
			return (NULL);
		if (thinking(all, philo_personal_number) != 0)
			return (NULL);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_all		all;
	t_params	params;
	int			i;

	if (!(argc == 5 || argc == 6))
		return (error_processing(E_ARG_NUM));
	if (init_all_params(&all, &params, argv, argc) != 0)
		return (error_processing(E_INIT));
	all.params = &params;
	i = 0;
	while (i < params.amount_of_philosophers)
	{
		if (pthread_create(&all.thread_id[i], NULL, &philosopher_routine, &all) != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	i = 0;
	while (i < params.amount_of_philosophers)
	{
		if (pthread_join(all.thread_id[i], NULL) != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}
	return (0);
}

























