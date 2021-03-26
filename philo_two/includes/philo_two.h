/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:04:31 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:57:20 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

# define E_ARG_NUM 10
# define E_ARG_NUM_TXT "ERROR: Wrong number of arguments"

# define E_WRONG_ARG 11
# define E_WRONG_ARG_TXT "ERROR: Wrong arguments"

# define E_MALLOC 12
# define E_MALLOC_TXT "ERROR: Mphoc failed"

# define JUST_FREE_ALL 0

typedef struct		s_params
{
	int				amount_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
}					t_params;

typedef struct		s_philo
{
	sem_t			*s_forks;
	sem_t			*s_for_getting_philo_number;
	sem_t			*s_is_philo_dead;
	sem_t			*s_output_protect;
	pthread_t		*thread_id;
	int				tmp_philo_num;
	struct timeval	initial_time;
	ssize_t			*time_of_last_meal;
	int				is_philo_dead;
	int				fed_philo_amount;
	t_params		params;
}					t_philo;

int					ft_atoi(const char *nbr);
int					philo_death(t_philo *ph, int philo_num);
int					get_philosopher_number(t_philo *ph);
int					put_forks(t_philo *ph);
int					right_fork_num(t_philo *ph, int philo_num);
unsigned int		get_current_timestamp(t_philo *ph);
int					check_philo_status(t_philo *ph);
unsigned int		print_status(t_philo *ph, int philo_num, char *action_kind);
void				pseudo_usleep(t_philo *ph, int philo_num, int action_time);
int					free_all(t_philo *ph, int error_number);
void				*philosopher_routine(void *arg);
void				*philo_is_full(t_philo *ph);

#endif
