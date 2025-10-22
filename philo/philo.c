/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:46:19 by beade-va          #+#    #+#             */
/*   Updated: 2025/10/19 01:01:48 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher(t_data *data, int i, int *full)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	if ((get_time() - data->philos[i].last_meal) >= data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		print_died(&data->philos[i]);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		return (1);
	}
	if (data->must_eat_count != -1
		&& data->philos[i].meals_eaten >= data->must_eat_count)
		(*full)++;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;
	int		i;
	int		full;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		i = 0;
		full = 0;
		while (i < data->number_philosophers)
		{
			if (check_philosopher(data, i, &full))
				return (NULL);
			i++;
		}
		if (data->must_eat_count != -1 && full == data->number_philosophers)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}
