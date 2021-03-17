/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:01:02 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 15:34:06 by fermelin         ###   ########.fr       */
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
	sem_t			*sem_for_getting_philo_number;
	pthread_t		*thread_id;
	int				*forks_status;
	int				tmp_philo_num;
	struct timeval	initial_time;
	ssize_t			*time_of_last_meal;
	int				is_philo_dead;
	t_params		params;
}					t_all;

int					ft_atoi(const char *nbr);
int					error_processing(int error_number, t_all *all);
int					init_all_params(t_all *all, char **argv, int argc);
int					philo_death(t_all *all, ssize_t timestamp,
					int philo_num);
int					get_philosopher_number(t_all *all);
int					thinking(t_all *all, int philo_num);
int					sleeping(t_all *all, int philo_num);
int					take_forks(t_all *all, int philo_num);
int					put_forks(t_all *all);
int					eating(t_all *all, int philo_num);
int					left_fork_num(t_all *all, int philo_num);
int					right_fork_num(t_all *all, int philo_num);
ssize_t				get_current_timestamp(t_all *all);

#endif
