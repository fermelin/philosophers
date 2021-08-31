

#include "philo_two.h"

static int	error_processing(int error_number, t_philo *ph)
{
	if (error_number == E_ARG_NUM)
		printf("%s\n", E_ARG_NUM_TXT);
	else if (error_number == E_WRONG_ARG)
		printf("%s\n", E_WRONG_ARG_TXT);
	else
		return (free_all(ph, error_number));
	return (error_number);
}

static int	init_philo_params_2(t_philo *ph)
{
	int	i;

	if (!(ph->time_of_last_meal = (ssize_t *)malloc(sizeof(ssize_t)
		* ph->params.amount_of_philosophers)))
		return (E_MALLOC);
	if (!(ph->thread_id = (pthread_t *)malloc(sizeof(pthread_t)
		* ph->params.amount_of_philosophers)))
		return (E_MALLOC);
	i = 0;
	while (i < ph->params.amount_of_philosophers)
		ph->time_of_last_meal[i++] = 0;
	if ((ph->s_for_getting_philo_number = sem_open(
		"s_for_getting_philo_number", O_CREAT | O_EXCL, 744, 1)) == SEM_FAILED)
		printf("s_for_getting_philo_number failed\n");
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

static int	init_philo_params(t_philo *ph, char **argv, int argc)
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
	ph->fed_philo_amount = 0;
	sem_unlink("s_for_getting_philo_number");
	sem_unlink("s_forks");
	sem_unlink("s_is_philo_dead");
	sem_unlink("s_output_protect");
	ph->tmp_philo_num = 0;
	ph->is_philo_dead = 0;
	ph->time_of_last_meal = NULL;
	ph->thread_id = NULL;
	return (init_philo_params_2(ph));
}

static int	death_checking(t_philo *ph)
{
	unsigned int	timestamp;
	int				i;

	while (1)
	{
		i = 0;
		timestamp = get_current_timestamp(ph);
		while (i < ph->params.amount_of_philosophers)
		{
			if (ph->fed_philo_amount == ph->params.amount_of_philosophers)
				return (0);
			if (timestamp - ph->time_of_last_meal[i] >= ph->params.time_to_die)
				return (philo_death(ph, i + 1));
			i++;
		}
		usleep(1000);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo		ph;
	int			i;
	int			error_number;

	if (!(argc == 5 || argc == 6))
		return (error_processing(E_ARG_NUM, &ph));
	if ((error_number = init_philo_params(&ph, argv, argc)) != 0)
		return (error_processing(error_number, &ph));
	i = 0;
	while (i < ph.params.amount_of_philosophers)
	{
		if (pthread_create(&ph.thread_id[i], NULL,
			&philosopher_routine, &ph) != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	death_checking(&ph);
	i = 0;
	while (i < ph.params.amount_of_philosophers)
	{
		if (pthread_join(ph.thread_id[i], NULL) != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}
	return (free_all(&ph, JUST_FREE_ALL));
}
