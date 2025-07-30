/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:48:12 by igngonza          #+#    #+#             */
/*   Updated: 2025/07/30 11:41:10 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

static int	check_philo_status(t_philo *philo, t_program *program)
{
	size_t	last_meal;
	size_t	now;

	pthread_mutex_lock(philo->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(philo->meal_lock);
	now = get_current_time() - program->start_time;
	if (now - last_meal > (size_t)program->time_to_die)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		state_change_printer(philo, now, ACTION_DIED);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers(t_program *program)
{
	int		i;
	int		all_ate_enough;
	t_philo	*philo;

	i = 0;
	all_ate_enough = 1;
	while (i < program->num_of_philos)
	{
		philo = &program->philos[i];
		if (program->num_times_to_eat > 0
			&& philo_get_meals(philo) >= program->num_times_to_eat)
		{
			i++;
			continue ;
		}
		if (check_philo_status(philo, program))
			return (1);
		all_ate_enough = 0;
		i++;
	}
	return (all_ate_enough == 1);
}

void	*global_supervisor(void *program_ptr)
{
	t_program	*program;

	program = (t_program *)program_ptr;
	while (1)
	{
		if (check_all_philosophers(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	size_t	now_ms;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	now_ms = get_current_time() - philo->program->start_time;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = now_ms;
	pthread_mutex_unlock(philo->meal_lock);
	philosopher_lifecycle(philo);
	return (NULL);
}

int	threads_loop(t_program *program)
{
	int			i;
	int			ret;
	pthread_t	supervisor_thread;

	ret = pthread_create(&supervisor_thread, NULL, global_supervisor, program);
	if (ret != 0)
		return (error(THEAD_ERR, program));
	i = 0;
	while (i < program->num_of_philos)
	{
		ret = pthread_create(&program->philos[i].thread, NULL, routine,
				&program->philos[i]);
		if (ret != 0)
			return (error(THEAD_ERR, program));
		i++;
	}
	pthread_join(supervisor_thread, NULL);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (error(JOIN_ERR, program));
		i++;
	}
	return (0);
}
