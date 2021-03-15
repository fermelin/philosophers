/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:04:31 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/15 18:05:39 by fermelin         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	int				tmp_philo_personal_number;
	struct timeval	initial_time;
	pthread_mutex_t	mutex_for_getting_philo_number;
	pthread_t		*thread_id;
	t_params		*params;
	// t_philo			*philos;
	ssize_t			*time_of_last_meal;
	int				is_philo_dead;

}					t_all;

// typedef struct		s_philo
// {
// 	// int		philo_personal_number;
// 	ssize_t	last_ate;

// }					t_philo;


int		ft_atoi(const char *nbr);

#endif
