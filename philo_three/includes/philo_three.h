/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:04:31 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/23 12:42:19 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <pthread.h>

# define E_ARG_NUM 10
# define E_ARG_NUM_TXT "ERROR: Wrong number of arguments"

# define E_WRONG_ARG 11
# define E_WRONG_ARG_TXT "ERROR: Wrong arguments"

# define E_MALLOC 12
# define E_MALLOC_TXT "ERROR: Malloc failed"

# define JUST_FREE_ALL 0

typedef struct		s_params
{
	int				amount_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
}					t_params;

typedef struct		s_all
{
	sem_t			*s_forks;
	sem_t			*s_is_philo_dead;
	sem_t			*s_output_protect;
	pthread_t		thread_id;
	int				philo_num;
	struct timeval	initial_time;
	ssize_t			time_of_last_meal;
	int				is_philo_dead;
	t_params		params;
}					t_all;

int					ft_atoi(const char *nbr);
int					philo_death(t_all *all, int philo_num);
int					get_philosopher_number(t_all *all);
int					put_forks(t_all *all);
int					right_fork_num(t_all *all, int philo_num);
unsigned int		get_current_timestamp(t_all *all);
int					check_philo_status(t_all *all);
unsigned int		print_status(t_all *all, int philo_num, char *action_kind);
void				pseudo_usleep(t_all *all, int action_time);
int					free_all(t_all *all, int error_number);
void				philosopher_routine(t_all all, int philo_num);
void				*death_checking(void *arg);

#endif
