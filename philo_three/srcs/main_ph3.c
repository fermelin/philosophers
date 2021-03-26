/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ph3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:58:02 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		error_processing(int error_number, t_philo *ph)
{
	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_WRONG_ARG)
		printf("%s\n", E_WRONG_ARG_TXT);
	else
		return (free_all(ph, error_number));
	return (error_number);
}

static int		init_philo_params_2(t_philo *ph)
{
	ph->time_of_last_meal = 0;
	if ((ph->s_forks = sem_open("s_forks", O_CREAT | O_EXCL, 744,
		ph->params.amount_of_philosophers)) == SEM_FAILED)
		printf("s_forks failed\n");
	if ((ph->s_is_philo_dead = sem_open("s_is_philo_dead", O_CREAT | O_EXCL,
		744, 1)) == SEM_FAILED)
		printf("s_is_philo_dead failed\n");
	if ((ph->s_output_protect = sem_open("s_output_protect", O_CREAT | O_EXCL,
		744, 1)) == SEM_FAILED)
		printf("s_output_protect failed\n");
	gettimeofday(&ph->initial_time, NULL);
	return (0);
}

static int		init_philo_params(t_philo *ph, char **argv, int argc)
{
	if ((ph->params.amount_of_philosophers = ft_atoi(argv[1])) < 2)
		return (E_WRONG_ARG);
	if ((ph->params.time_to_die = ft_atoi(argv[2])) < 0)
		return (E_WRONG_ARG);
	if ((ph->params.time_to_eat = ft_atoi(argv[3])) < 0)
		return (E_WRONG_ARG);
	if ((ph->params.time_to_sleep = ft_atoi(argv[4])) < 0)
		return (E_WRONG_ARG);
	if (argc == 6)
	{
		if ((ph->params.times_must_eat = ft_atoi(argv[5])) < 1)
			return (E_WRONG_ARG);
	}
	else
		ph->params.times_must_eat = -1;
	sem_unlink("s_forks");
	sem_unlink("s_is_philo_dead");
	sem_unlink("s_output_protect");
	ph->is_philo_dead = 0;
	ph->philo_num = 0;
	return (init_philo_params_2(ph));
}

void			*death_checking(void *arg)
{
	t_philo			*ph;
	unsigned int	timestamp;

	ph = (t_philo *)arg;
	while (1)
	{
		timestamp = get_current_timestamp(ph);
		if (timestamp - ph->time_of_last_meal >= ph->params.time_to_die)
		{
			philo_death(ph, ph->philo_num);
			return (NULL);
		}
		usleep(1000);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_philo		ph;
	int			i;
	int			error_number;

	if (!(argc == 5 || argc == 6))
		return (error_processing(E_ARG_NUM, &ph));
	if ((error_number = init_philo_params(&ph, argv, argc)) != 0)
		return (error_processing(error_number, &ph));
	while (ph.philo_num < ph.params.amount_of_philosophers)
	{
		ph.philo_num++;
		if (fork() == 0)
			philosopher_routine(ph, ph.philo_num);
	}
	i = 0;
	while (i < ph.params.amount_of_philosophers)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (free_all(&ph, JUST_FREE_ALL));
}
