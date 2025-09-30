/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:34:18 by beade-va          #+#    #+#             */
/*   Updated: 2025/09/30 18:56:15 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	monitor;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data))
		return (1);
	init_all(&data);
	data.start_time = get_time();
	init_philo_routine(&data);
	if (pthread_create(&monitor, NULL, monitor_thread, &data) != 0)
	{
		ft_putstr("Error: monitor creation failed\n");
		return (1);
	}
	i = 0;
	while (i < data.number_philosophers)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	clean_thread(&data);
	return (0);
}

int	init_all(t_data *data)
{
	if (init_forks(data))
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->state, NULL) != 0)
		return (ft_putstr("Error: mutex init failed\n"), 1);
	if (init_philosophers(data))
		return (1);
	return (0);
}

int	init_philo_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philosophers)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			ft_putstr("Error: thread creation failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	clean_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state);
	free(data->forks);
	free(data->philos);
}
