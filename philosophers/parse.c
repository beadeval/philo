/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:25:06 by beade-va          #+#    #+#             */
/*   Updated: 2025/09/30 18:56:44 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		ft_putstr("Error: Invalid number of parameters.\n");
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		ft_putstr("Error: Simulation cannot start with only 1 philosopher.\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!validate_arg(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (check_args(argc, argv))
		return (1);
	data->number_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	return (0);
}

int	validate_arg(char *str)
{
	if (!is_number(str))
	{
		ft_putstr("Error: Argument must contain only digits.\n");
		return (0);
	}
	if (!is_positive(str))
	{
		ft_putstr("Error: Argument must be greater than 0.\n");
		return (0);
	}
	return (1);
}
