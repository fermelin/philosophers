/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/16 20:04:21 by fermelin         ###   ########.fr       */
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
	if (!(all->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* params->amount_of_philosophers)))
		return (1);
	if (!(all->time_of_last_meal = (ssize_t *)malloc(sizeof(ssize_t)
		* params->amount_of_philosophers)))
		return (1);
	if (!(all->forks_status = (int *)malloc(sizeof(int)
		* params->amount_of_philosophers)))
		return (1);
	i = 0;
	while (i < params->amount_of_philosophers)
	{
		pthread_mutex_init(&all->m_forks[i], NULL);
		all->time_of_last_meal[i] = 0;
		all->forks_status[i] = i + 1 - i % 2;
		// printf("fork status for %d is %d\n", i, all->forks_status[i]);
		i++;
	}
	pthread_mutex_init(&all->mutex_for_getting_philo_number, NULL);
	// memset(all->m_forks, 0, (sizeof(int) * params->amount_of_philosophers));
	if (!(all->thread_id =(pthread_t *)malloc(sizeof(pthread_t)
		* params->amount_of_philosophers)))
		return (1);
	gettimeofday(&all->initial_time, NULL);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_all	*all;
	int		philo_personal_number;
	int		i;

	all = (t_all *)arg;
	philo_personal_number = get_philosopher_number(all);
	// printf("philo number is %d\n", philo_personal_number);
	i = 0;
	while (1)
	{
		if (take_forks(all, philo_personal_number) != 0)
			continue ;
		if (eating(all, philo_personal_number) != 0)
			return (NULL);
		i++;
		if (all->params->times_must_eat != -1 && all->params->times_must_eat == i)
			break ;
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
