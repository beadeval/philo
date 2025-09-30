/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:02 by beade-va          #+#    #+#             */
/*   Updated: 2025/09/30 18:53:51 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_routine(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_routine(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_routine(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_routine(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philos)
{
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

void	is_sleeping(t_philo *philos)
{
	long	time_start;

	time_start = get_time();
	print_routine(philos, "is sleeping");
	while (!philos->data->dead && (get_time()
			- time_start < philos->data->time_to_sleep))
		ft_usleep(500);
}

void	is_thinking(t_philo *philos)
{
	print_routine(philos, "is thinking");
}

void	is_eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->dead)
	{
		put_forks(philo);
		return ;
	}
	print_routine(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
