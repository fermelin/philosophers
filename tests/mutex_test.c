/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:20:01 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/26 12:55:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


typedef struct s_philo
{
	int 			smth;
	int				threads_amount;
	pthread_mutex_t mutex;
	pthread_mutex_t mutex_for_thread_ids;
	unsigned long	*thread_ids;
}				t_philo;

int h_g = 0;

int		get_thread_number(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph->threads_amount)
	{
		if (ph->thread_ids[i] == 0)
		{
			pthread_mutex_lock(&ph->mutex_for_thread_ids);
			ph->thread_ids[i] = (unsigned long)pthread_self();
			pthread_mutex_unlock(&ph->mutex_for_thread_ids);
			break ;
		}
		i++;
	}
	return (i);
}

void	*routine(void *structure)
{

	t_philo *ph = (t_philo*)structure;
	int loops = ph->smth;
	int loc, i, what_thread;
	// unsigned long self_thread_id = (unsigned long)pthread_self();
	what_thread = get_thread_number(ph);
	i = 0;
	while (i < loops)
	{
		pthread_mutex_lock(&ph->mutex);
		loc = h_g;
		loc++;
		h_g = loc;
		i++;
		pthread_mutex_unlock(&ph->mutex);
		// printf("%lu\n", self_thread_id);
		if (!(i % 1000))
			printf("%d\n", what_thread);
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	t_philo 				ph;
	pthread_t			*thread_id;
	int					i;
	int					status;


	ph.smth = (argc > 1) ? atoi(argv[1]) : 10000000;
	pthread_mutex_init(&ph.mutex, NULL);
	pthread_mutex_init(&ph.mutex_for_thread_ids, NULL);

	ph.threads_amount = (argc > 2) ? atoi(argv[2]) : 5;
	if (!(ph.thread_ids = (unsigned long*)malloc(sizeof(unsigned long) * ph.threads_amount)))
		return (0);
	memset(ph.thread_ids, 0, (sizeof(unsigned long) * ph.threads_amount));
	if (!(thread_id = (pthread_t*)malloc(sizeof(pthread_t) * ph.threads_amount)))
		return (0);
	i = 0;
	while (i < ph.threads_amount)
	{
		status = pthread_create(&thread_id[i], NULL, &routine, &ph);
		if (status != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	i = 0;
	while (i < ph.threads_amount)
	{
		status = pthread_join(thread_id[i], NULL);
		if (status != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}
	printf("%d\n", h_g);

}