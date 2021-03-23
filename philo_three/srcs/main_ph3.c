/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ph3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/23 12:42:21 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		error_processing(int error_number, t_all *all)
{
	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_WRONG_ARG)
		printf("%s\n", E_WRONG_ARG_TXT);
	else
		return (free_all(all, error_number));
	return (error_number);
}

static int		init_all_params_2(t_all *all)
{
	all->time_of_last_meal = 0;
	if ((all->s_forks = sem_open("s_forks", O_CREAT | O_EXCL, 744,
		all->params.amount_of_philosophers)) == SEM_FAILED)
		printf("s_forks failed\n");
	if ((all->s_is_philo_dead = sem_open("s_is_philo_dead", O_CREAT | O_EXCL,
		744, 1)) == SEM_FAILED)
		printf("s_is_philo_dead failed\n");
	if ((all->s_output_protect = sem_open("s_output_protect", O_CREAT | O_EXCL,
		744, 1)) == SEM_FAILED)
		printf("s_output_protect failed\n");
	gettimeofday(&all->initial_time, NULL);
	return (0);
}

static int		init_all_params(t_all *all, char **argv, int argc)
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
	sem_unlink("s_forks");
	sem_unlink("s_is_philo_dead");
	sem_unlink("s_output_protect");
	all->is_philo_dead = 0;
	all->philo_num = 0;
	return (init_all_params_2(all));
}

void			*death_checking(void *arg)
{
	t_all			*all;
	unsigned int	timestamp;

	all = (t_all *)arg;
	while (1)
	{
		timestamp = get_current_timestamp(all);
		if (timestamp - all->time_of_last_meal >= all->params.time_to_die)
		{
			philo_death(all, all->philo_num);
			return (NULL);
		}
		usleep(1000);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_all		all;
	int			i;
	int			error_number;

	if (!(argc == 5 || argc == 6))
		return (error_processing(E_ARG_NUM, &all));
	if ((error_number = init_all_params(&all, argv, argc)) != 0)
		return (error_processing(error_number, &all));
	while (all.philo_num < all.params.amount_of_philosophers)
	{
		all.philo_num++;
		if (fork() == 0)
			philosopher_routine(all, all.philo_num);
	}
	i = 0;
	while (i < all.params.amount_of_philosophers)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (free_all(&all, JUST_FREE_ALL));
}
