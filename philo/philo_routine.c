/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:51:30 by beade-va          #+#    #+#             */
/*   Updated: 2025/10/08 00:22:57 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->data->number_philosophers == 1)
	{
		print_routine(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (NULL);
	}
	while (!philo->data->dead)
	{
		if (philo->id % 2 != 0)
			ft_usleep(1);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
