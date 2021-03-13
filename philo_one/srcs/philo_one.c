/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/13 17:32:02 by fermelin         ###   ########.fr       */
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
	params->number_of_philisophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->tme_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->times_must_eat = ft_atoi(argv[5]);
	else
		params->times_must_eat = 0;
	if (!(all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* params->number_of_philisophers)))
		return (1);
	memset(all->forks, 0, (sizeof(int) * params->number_of_philisophers));
	if (!(all->thread_id =(pthread_t *)malloc(sizeof(pthread_t)
		* params->number_of_philisophers)))
		return (1);
}

int		thinking(t_params *params)
{
	usleep(params->time_to_sleep * 1000);
	return (0);
}

int		sleeping(t_params *params)
{
	usleep(params->time_to_sleep * 1000);
	return (0);
}

int		eating(t_params *params)
{
	struct timeval before;
	struct timeval after;

	gettimeofday(&before, NULL);
	usleep(params->time_to_eat * 1000);
	gettimeofday(&after, NULL);
	printf()
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	eating(t_params *params)
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
	all->params = &params;
	i = 0;
	while (i < all.threads_amount)
	{
		if (pthread_create(&all->thread_id[i], NULL, &philosopher_routine, &all) != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	i = 0;
	while (i < all.threads_amount)
	{
		if (pthread_join(thread_id[i], NULL) != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}







}

void	get_philosopher_number(void)
{
	while 
}
























