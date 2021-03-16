/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:04:31 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/16 16:35:49 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

# define E_ARG_NUM 10
# define E_ARG_NUM_TXT "ERROR: Wrong number of arguments"

# define E_INIT 11
# define E_INIT_TXT "ERROR: Init failed"

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
	pthread_mutex_t	*m_forks;
	int				*forks_status;
	int				tmp_philo_personal_number;
	struct timeval	initial_time;
	pthread_mutex_t	mutex_for_getting_philo_number;
	pthread_t		*thread_id;
	t_params		*params;
	// t_philo			*philos;
	ssize_t			*time_of_last_meal;
	short int		is_philo_dead;

}					t_all;

// typedef struct		s_philo
// {
// 	// int		philo_personal_number;
// 	ssize_t	last_ate;

// }					t_philo;


int		ft_atoi(const char *nbr);
int		error_processing(int error_number);
int		init_all_params(t_all *all, t_params *params, char **argv, int argc);
int		philo_death(t_all *all, ssize_t timestamp, int philo_personal_number);
int		get_philosopher_number(t_all *all);
int		thinking(t_all *all, int philo_personal_number);
int		sleeping(t_all *all, int philo_personal_number);
int		take_forks(t_all *all, int philo_personal_number);
int		put_forks(t_all *all, int philo_personal_number);
int		eating(t_all *all, int philo_personal_number);
int		left_fork_num(t_all *all, int philo_personal_number);
int		right_fork_num(t_all *all, int philo_personal_number);
ssize_t	get_current_timestamp(t_all *all);

#endif
