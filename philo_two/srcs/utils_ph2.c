

#include "philo_two.h"

int				free_all(t_philo *ph, int error_number)
{
	if (error_number == JUST_FREE_ALL)
	{
		sem_close(ph->s_for_getting_philo_number);
		sem_close(ph->s_forks);
		sem_close(ph->s_is_philo_dead);
		sem_close(ph->s_output_protect);
		sem_unlink("s_for_getting_philo_number");
		sem_unlink("s_forks");
		sem_unlink("s_is_philo_dead");
		sem_unlink("s_output_protect");
	}
	free(ph->time_of_last_meal);
	free(ph->thread_id);
	if (error_number == E_MALLOC)
		printf("%s\n", E_MALLOC_TXT);
	return (error_number);
}

int				right_fork_num(t_philo *ph, int philo_index)
{
	return ((philo_index + 1) % ph->params.amount_of_philosophers);
}

int				philo_death(t_philo *ph, int philo_num)
{
	unsigned int	timestamp;

	if (check_philo_status(ph) == 0)
	{
		timestamp = get_current_timestamp(ph);
		sem_wait(ph->s_is_philo_dead);
		ph->is_philo_dead = 1;
		sem_post(ph->s_is_philo_dead);
		sem_wait(ph->s_output_protect);
		printf("%u %d died\n", timestamp, philo_num);
		sem_post(ph->s_output_protect);
	}
	return (1);
}

int				get_philosopher_number(t_philo *ph)
{
	int		tmp_philo_number;

	sem_wait(ph->s_for_getting_philo_number);
	ph->tmp_philo_num++;
	tmp_philo_number = ph->tmp_philo_num;
	sem_post(ph->s_for_getting_philo_number);
	return (tmp_philo_number);
}

unsigned int	get_current_timestamp(t_philo *ph)
{
	struct timeval	current_time;
	unsigned int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - ph->initial_time.tv_sec) * 1000
	+ (current_time.tv_usec - ph->initial_time.tv_usec) / 1000;
	return (timestamp);
}
