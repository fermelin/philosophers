/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:50:10 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/15 15:02:54 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	int retval;
	long int sec;
	long int  mins;
	long int  hrs;
	long int  days;
	long int  yrs;
	struct timeval tp;

	retval = 0;
	retval = gettimeofday(&tp, NULL);
	sec = tp.tv_usec / 1000;
	mins = sec / 60;
	hrs = mins / 60;
	days = hrs / 24;
	yrs = days / 365;
	printf("sec %ld\n", sec);
	printf("mins %ld\n", mins);
	printf("hrs %ld\n", hrs);
	printf("days %ld\n", days);
	printf("yrs %ld\n", yrs);
	return (0);
}