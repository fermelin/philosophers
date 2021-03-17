/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_philo_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:52 by fermelin          #+#    #+#             */
/*   Updated: 2021/03/17 19:02:34 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_philo_status(t_all *all)
{
	int	status;

	pthread_mutex_lock(&all->m_is_philo_dead);
	status = all->is_philo_dead;
	pthread_mutex_unlock(&all->m_is_philo_dead);
	return (status);
}