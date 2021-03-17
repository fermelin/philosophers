/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:20:01 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 14:02:05 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


typedef struct s_all
{
	int 			smth;
	int				threads_amount;
	pthread_mutex_t mutex;
	pthread_mutex_t mutex_for_thread_ids;
	unsigned long	*thread_ids;
}				t_all;

int h_g = 0;

int		get_thread_number(t_all *all)
{
	int i;

	i = 0;
	while (i < all->threads_amount)
	{
		if (all->thread_ids[i] == 0)
		{
			pthread_mutex_lock(&all->mutex_for_thread_ids);
			all->thread_ids[i] = (unsigned long)pthread_self();
			pthread_mutex_unlock(&all->mutex_for_thread_ids);
			break ;
		}
		i++;
	}
	return (i);
}

void	*routine(void *structure)
{

	t_all *all = (t_all*)structure;
	int loops = all->smth;
	int loc, i, what_thread;
	// unsigned long self_thread_id = (unsigned long)pthread_self();
	what_thread = get_thread_number(all);
	i = 0;
	while (i < loops)
	{
		pthread_mutex_lock(&all->mutex);
		loc = h_g;
		loc++;
		h_g = loc;
		i++;
		pthread_mutex_unlock(&all->mutex);
		// printf("%lu\n", self_thread_id);
		if (!(i % 1000))
			printf("%d\n", what_thread);
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	t_all 				all;
	pthread_t			*thread_id;
	int					i;
	int					status;


	all.smth = (argc > 1) ? atoi(argv[1]) : 10000000;
	pthread_mutex_init(&all.mutex, NULL);
	pthread_mutex_init(&all.mutex_for_thread_ids, NULL);

	all.threads_amount = (argc > 2) ? atoi(argv[2]) : 5;
	if (!(all.thread_ids = (unsigned long*)malloc(sizeof(unsigned long) * all.threads_amount)))
		return (0);
	memset(all.thread_ids, 0, (sizeof(unsigned long) * all.threads_amount));
	if (!(thread_id = (pthread_t*)malloc(sizeof(pthread_t) * all.threads_amount)))
		return (0);
	i = 0;
	while (i < all.threads_amount)
	{
		status = pthread_create(&thread_id[i], NULL, &routine, &all);
		if (status != 0)
			printf("%d pthread_create error\n", i);
		i++;
	}
	i = 0;
	while (i < all.threads_amount)
	{
		status = pthread_join(thread_id[i], NULL);
		if (status != 0)
			printf("%d pthread_join error\n", i);
		i++;
	}
	printf("%d\n", h_g);

}