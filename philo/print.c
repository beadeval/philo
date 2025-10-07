/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:10:23 by beade-va          #+#    #+#             */
/*   Updated: 2025/10/08 00:24:20 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_routine(t_philo *philos, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philos->data->print_mutex);
	if (!philos->data->dead)
	{
		timestamp = get_time() - philos->data->start_time;
		printf("%ld %d %s\n", timestamp, philos->id, action);
	}
	pthread_mutex_unlock(&philos->data->print_mutex);
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%li %d died\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
