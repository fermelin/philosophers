/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 18:59:42 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		error_processing(int error_number, t_all *all)
{
	int i;

	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_WRONG_ARG)
		printf("%s\n", E_WRONG_ARG_TXT);
	else if (error_number == JUST_FREE_ALL)
	{
		i = 0;
		while (i < all->params.amount_of_philosophers)
			if (pthread_mutex_destroy(&all->m_forks[i++]) != 0)
				printf("mutex_destroy error\n");
		pthread_mutex_destroy(&all->mutex_for_getting_philo_number);
		pthread_mutex_destroy(&all->m_is_philo_dead);

	}
	if (error_number == E_MALLOC || error_number == JUST_FREE_ALL)
	{
		free(all->m_forks);
		free(all->time_of_last_meal);
		free(all->forks_status);
		free(all->thread_id);
		if (error_number == E_MALLOC)
			printf("%s\n", E_MALLOC_TXT);
	}
	return (error_number);
}

int		init_all_params_2(t_all *all)
{
	int	i;

	if (!(all->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* all->params.amount_of_philosophers)))
		return (E_MALLOC);
	if (!(all->time_of_last_meal = (ssize_t *)malloc(sizeof(ssize_t)
		* all->params.amount_of_philosophers)))
		return (E_MALLOC);
	if (!(all->forks_status = (int *)malloc(sizeof(int)
		* all->params.amount_of_philosophers)))
		return (E_MALLOC);
	if (!(all->thread_id = (pthread_t *)malloc(sizeof(pthread_t)
		* all->params.amount_of_philosophers)))
		return (E_MALLOC);
	i = 0;
	while (i < all->params.amount_of_philosophers)
	{
		pthread_mutex_init(&all->m_forks[i], NULL);
		all->time_of_last_meal[i] = 0;
		all->forks_status[i] = i + 1 - i % 2;
		i++;
	}
	
	gettimeofday(&all->initial_time, NULL);
	return (0);
}

int		init_all_params(t_all *all, char **argv, int argc)
{
	if ((all->params.amount_of_philosophers = ft_atoi(argv[1])) < 2)
		return (E_WRONG_ARG);
	if ((all->params.time_to_die = ft_atoi(argv[2])) < 0)
		return (E_WRONG_ARG);
	if ((all->params.time_to_eat = ft_atoi(argv[3])) < 0)
		return (E_WRONG_ARG);
	if ((all->params.time_to_sleep = ft_atoi(argv[4])) < 0)
		return (E_WRONG_ARG);
	if (argc == 6)
	{
		if ((all->params.times_must_eat = ft_atoi(argv[5])) < 1)
			return (E_WRONG_ARG);
	}
	else
		all->params.times_must_eat = -1;
	all->tmp_philo_num = 0;
	all->is_philo_dead = 0;
	all->m_forks = NULL;
	all->time_of_last_meal = NULL;
	all->forks_status = NULL;
	all->thread_id = NULL;
	pthread_mutex_init(&all->mutex_for_getting_philo_number, NULL);
	pthread_mutex_init(&all->m_is_philo_dead, NULL);
	return (init_all_params_2(all));
}

void	*philosopher_routine(void *arg)
{
	t_all	*all;
	int		philo_num;
	int		i;

	all = (t_all *)arg;
	philo_num = get_philosopher_number(all);
	i = 0;
	while (1)
	{
		if (take_forks(all, philo_num) != 0)
			continue ;
		if (eating(all, philo_num) != 0)
			return (NULL);
		i++;
		if (all->params.times_must_eat != -1 && all->params.times_must_eat == i)
			break ;
		if (sleeping(all, philo_num) != 0)
			return (NULL);
		if (thinking(all, philo_num) != 0)
			return (NULL);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_all		all;
	int			i;
	int			error_number;

	if (!(argc == 5 || argc == 6))
		return (error_processing(E_ARG_NUM, &all));
	if ((error_number = init_all_params(&all, argv, argc)) != 0)
		return (error_processing(error_number, &all));
	i = 0;
	while (i < all.params.amount_of_philosophers)
	{
		if (pthread_create(&all.thread_id[i], NULL,
			&philosopher_routine, &all) != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	i = 0;
	while (i < all.params.amount_of_philosophers)
	{
		if (pthread_join(all.thread_id[i], NULL) != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}
	return (error_processing(JUST_FREE_ALL, &all));
}