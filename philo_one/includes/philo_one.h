/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:04:31 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/13 17:32:03 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define E_ARG_NUM 10
# define E_ARG_NUM_TXT "ERROR: Wrong number of arguments"

# define E_INIT 11
# define E_INIT_TXT "ERROR: Init failed"

typedef struct		s_params
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
}					t_params;


typedef struct		s_all
{
	pthread_mutex_t	*forks;
	// pthread_mutex_t	mutex;
	pthread_t		*thread_id;
	t_params		*params;

}					t_all;


int		ft_atoi(const char *nbr)

#endif
