/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:33:14 by beade-va          #+#    #+#             */
/*   Updated: 2025/10/12 22:23:18 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	int				number_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long int		start_time;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	dead_mutex;

	int				dead;
	struct s_philo	*philos;

}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;

	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;

	struct s_data	*data;
}					t_philo;

// Utils
int					is_number(char *str);
int					is_positive(char *str);
int					ft_atoi(const char *nptr);

// Get time
long				get_time(void);
void				ft_usleep(long ms);

// Inits
int					init_forks(t_data *data);
int					init_print(t_data *data);
int					init_philosophers(t_data *data);

// Parseo
int					parse_args(int argc, char **argv, t_data *data);
int					validate_arg(char *str);
int					check_args(int argc, char **argv);

// Utils parseo
int					is_number(char *str);
int					is_positive(char *str);
int					ft_atoi(const char *nptr);
void				ft_putstr(char *s);

// Routine
void				is_sleeping(t_philo *philos);
void				is_thinking(t_philo *philos);
void				is_eating(t_philo *philos);
void				put_forks(t_philo *philos);
void				take_forks(t_philo *philos);
void				*philo_routine(void *arg);

// Philosophers
int					join_thread(t_data *data);
void				*monitor_thread(void *arg);
int					check_philosopher(t_data *data, int i, int *full);

// Print
void				print_routine(t_philo *philos, char *action);
void				print_(t_philo *philo);
void				print_died(t_philo *philo);

// Main
int					init_all(t_data *data);
int					init_philo_routine(t_data *data);
void				clean_thread(t_data *data);
