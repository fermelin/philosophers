/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:37:27 by fermelin          #+#    #+#             */
/*   Updated: 2021/02/19 16:52:54 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

int


     gettimeofday(struct timeval *restrict tp, void *restrict tzp);

int	main(void)
{
	struct timeval tp;

	gettimeofday(&tp, NULL);
	printf("%ld\n", tp.tv_sec);
	printf("%d\n", tp.tv_usec);

	return (0);
}