/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:00:14 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 13:10:31 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "parse_args.h"
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define ACTION_TAKE_FORK "has taken a fork"
# define ACTION_EATING "is eating"
# define ACTION_THINKING "is thinking"
# define ACTION_SLEEPING "is sleeping"
# define ACTION_DIED "died"

typedef struct s_program	t_program;

typedef struct s_philo
{
	int						id;
	int						meals_eaten;
	size_t					last_meal_time;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	int						num_times_to_eat;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*write_lock;
	pthread_mutex_t			*dead_lock;
	pthread_mutex_t			*meal_lock;
	t_program				*program;
	pthread_t				thread;
}							t_philo;

typedef struct s_program
{
	int						num_of_philos;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					start_time;
	int						num_times_to_eat;
	int						dead_flag;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			write_lock;
	pthread_mutex_t			*forks;
	t_philo					*philos;
}							t_program;

int							init(t_program *program, char **argv, int argc);
void						*routine(void *philos);
int							threads_loop(t_program *program);
void						eating_process(t_philo *philo);
int							philo_is_dead(t_philo *philo);
void						free_resources(t_program *program);
void						philosopher_lifecycle(t_philo *philo);
void						mark_dead_flag(t_philo *philo);
int							philo_get_meals(t_philo *philo);
#endif