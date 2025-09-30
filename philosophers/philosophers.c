/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:46:19 by beade-va          #+#    #+#             */
/*   Updated: 2025/09/30 18:59:02 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philo(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->number_philosophers)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->number_philosophers)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine,
			&data->philos[i]);
		i++;
	}
	join_thread(data);
	return (0);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philosophers)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Thread join failed");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead)
	{
		i = 0;
		while (i < data->number_philosophers)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if ((get_time() - data->philos[i].last_meal) >= data->time_to_die)
			{
				data->dead = 1;
				print_died(&data->philos[i]);
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
		usleep(1000); 
	}
	return (NULL);
}
