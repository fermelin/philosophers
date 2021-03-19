/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/19 12:13:51 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		error_processing(int error_number, t_all *all)
{
	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_WRONG_ARG)
		printf("%s\n", E_WRONG_ARG_TXT);
	else
		return (free_all(all, error_number));
	return (error_number);
}

int		init_all_params_2(t_all *all)
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
	sem_unlink("s_forks");
	sem_unlink("s_is_philo_dead");
	sem_unlink("s_output_protect");
	all->is_philo_dead = 0;
	return (init_all_params_2(all));
}

void	philosopher_routine(t_all all, int philo_num)
{
	int		i;

	i = 0;
	while (1)
	{
		if (take_forks(&all, philo_num) != 0)
			continue ;
		if (eating(&all, philo_num) != 0)
			exit(1);
		i++;
		if (all.params.times_must_eat != -1 && all.params.times_must_eat == i)
			exit(0);
		if (sleeping(&all, philo_num) != 0)
			exit(1);
		if (thinking(&all, philo_num) != 0)
			exit(1);
	}
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
		i++;
		if (fork() == 0)
			philosopher_routine(all, i);
	}
	i = 0;
	waitpid(-1, NULL, 0);
	kill(0, SIGTERM);
	return (free_all(&all, JUST_FREE_ALL));
}
