/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:02 by beade-va          #+#    #+#             */
/*   Updated: 2025/10/19 01:40:36 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	is_eating(t_philo *philo)
{
	take_forks(philo);
	if (is_dead(philo->data))
	{
		put_forks(philo);
		return ;
	}
	print_routine(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	put_forks(philo);
}

void	is_sleeping(t_philo *philo)
{
	print_routine(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	print_routine(philo, "is thinking");
}
