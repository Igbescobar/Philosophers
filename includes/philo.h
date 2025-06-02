/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:00:14 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/02 11:06:50 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "parse_args.h"
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_program t_program; // Forward declaration for t_program

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	t_program *program; // Reference to the program struct
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_times_to_eat;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t fork_lock; // Shared mutex for fork acquisition
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_program;

int					init(t_program *program, char **argv, int argc);
void				*routine(void *philos);
int					threads_loop(t_program *program);
void				eating_process(t_philo *philo);
int					philo_is_dead(t_philo *philo);
#endif