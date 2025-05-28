/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:21:03 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/26 17:01:02 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mallocs(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (!program->philos)
		return (0);
	while (i < program->num_of_philos)
	{
		program->philos[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (!program->philos[i].r_fork)
			return (0);
		program->philos[i].l_fork = malloc(sizeof(pthread_mutex_t));
		if (!program->philos[i].l_fork)
			return (0);
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].dead = &program->dead_flag;
		i++;
	}
	return (1);
}

static int	init_program_struct(int argc, char **argv, t_philo *program)
{
	program->num_of_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->num_times_to_eat = ft_atoi(argv[5]);
	else
		program->num_times_to_eat = -1;
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal_time = 0;
		program->philos[i].time_to_die = program->time_to_die;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].start_time = get_current_time();
		program->philos[i].num_of_philos = program->num_of_philos;
		program->philos[i].num_times_to_eat = program->num_times_to_eat;
		i++;
	}
	return (1);
}

int	init(t_program *program, char **argv, int argc)
{
	if (!init_program_struct(argc, argv, program))
		return (0);
	if (!init_mallocs(program))
		return (0);
	if (!init_philos(program))
		return (0);
	return (0);
}
