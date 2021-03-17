/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:03:07 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 14:55:39 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

/*int sem_post(sem_t *sem); - The semaphore referenced by sem is unlocked, the value of the semaphore is incremented, and all threads which are waiting on the semaphore are awakened.
**
** sem_t *sem_open(const char *name, int oflag, ...); - sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
** If O_CREAT is specified, sem_open() requires an additional two arguments.The parameters "mode_t mode" and "unsigned int value" are optional.
**
** int sem_close(sem_t *sem);
**
** int sem_unlink(const char *name);
**
** int sem_post(sem_t *sem)
**
** int sem_wait(sem_t *sem)

*/
int		main(void)
{
	sem_t	*sem_forks;
	int i;

	if (sem_close(sem_forks) != 0)
		printf("sem_close failed with errno code %s\n", strerror(errno));
	if (sem_unlink("sem_forks") != 0)
		printf("sem_unlink failed with errno code %s\n", strerror(errno));
	i = 0;
	if ((sem_forks = sem_open("sem_forks", O_CREAT, 744, 5)) == SEM_FAILED)
	{
		printf("sem_open failed\n");
		return (0);
	}
	while (i < 6)
	{
		sem_wait(sem_forks);
		printf("i = %d\n", i);
		i++;
	}
	if (sem_close(sem_forks) != 0)
		printf("sem_close failed with errno code %s\n", strerror(errno));
	if (sem_unlink("sem_forks") != 0)
		printf("sem_unlink failed with errno code %s\n", strerror(errno));

	return (0);




}