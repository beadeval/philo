/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:29:33 by beade-va          #+#    #+#             */
/*   Updated: 2025/09/30 19:05:09 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philosophers);
	if (!data->forks)
		return (ft_putstr("Error: malloc failed (init forks)\n"), 1);
	i = 0;
	while (i < data->number_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_putstr("Error: mutex init failed\n"), 1);
		i++;
	}
	return (0);
}

int	init_print(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_putstr("Error: mutex init failed\n"), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_philosophers);
	if (!data->philos)
		return (ft_putstr("Error: malloc failed\n"), 1);
	pthread_mutex_init(&data->state, NULL);
	data->start_time = get_time();
	i = 0;
	while (i < data->number_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->number_philosophers];
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (ft_putstr("Error: mutex init failed\n"), 1);
		i++;
	}
	return (0);
}
