/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:35:54 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/11 18:19:13 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_all
{
	int 			smth;
	pthread_mutex_t mutex;
}				t_all;

int h_g = 0;

void	*routine(void *structure)
{

	t_all *all = (t_all*)structure;
	int loops = all->smth;
	int loc, i;
	unsigned long self_thread_id = (unsigned long)pthread_self();

	i = 0;
	while (i < loops)
	{
		// pthread_mutex_lock(&all->mutex);
		loc = h_g;
		loc++;
		h_g = loc;
		i++;
		// pthread_mutex_unlock(&all->mutex);
		// printf("%lu\n", self_thread_id);
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	t_all structure;
	pthread_t			thread_id;
	pthread_t			thread_id1;
	unsigned long int	i;
	int					status;


	structure.smth = (argc > 1) ? atoi(argv[1]) : 10000000;
	pthread_mutex_init(&structure.mutex, NULL);
	i = 0;
	status = pthread_create(&thread_id, NULL, &routine, &structure);
	if (status != 0)
		printf("%s\n", "pthread_create error");
	// routine(smth);
	status = pthread_create(&thread_id1, NULL, &routine, &structure);
	if (status != 0)
		printf("%s\n", "pthread_create error");

	status = pthread_join(thread_id, NULL);
	if (status != 0)
		printf("%s\n", "pthread_join error");
	status = pthread_join(thread_id1, NULL);
	if (status != 0)
		printf("%s\n", "pthread_join error");

	printf("%d\n", h_g);

}

int		main(int argc, char **argv)
{
	t_all 	all;

	if (argc != 5 || argc != 6)
	{
		printf("ERROR: Wrong number of arguments\n");
		return (0);
	}
	

}

























