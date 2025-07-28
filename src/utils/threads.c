/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:48:12 by igngonza          #+#    #+#             */
/*   Updated: 2025/07/28 13:41:53 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

int	philo_is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->program->dead_lock);
	dead = philo->program->dead_flag;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (dead);
}

static int	check_philosopher_death(t_philo *philo)
{
	size_t	now_ms;
	size_t	last_meal;

	pthread_mutex_lock(philo->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(philo->meal_lock);
	now_ms = get_current_time() - philo->program->start_time;
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (1);
	}
	if (now_ms - last_meal > philo->program->time_to_die)
	{
		philo->program->dead_flag = 1;
		pthread_mutex_unlock(&philo->program->dead_lock);
		now_ms = get_current_time() - philo->program->start_time;
		state_change_printer(philo, now_ms, ACTION_DIED);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;
	int		max_eats;

	philo = (t_philo *)philo_pointer;
	max_eats = philo->program->num_times_to_eat;
	while (!philo_is_dead(philo) && (max_eats < 0
			|| philo_get_meals(philo) < max_eats))
	{
		if (check_philosopher_death(philo))
			break ;
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo		*philo;
	pthread_t	supervisor_thread;
	size_t		now_ms;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	now_ms = get_current_time() - philo->program->start_time;
	philo->last_meal_time = now_ms;
	if (pthread_create(&supervisor_thread, NULL, supervisor, philo) != 0)
	{
		now_ms = get_current_time() - philo->program->start_time;
		return (state_change_printer(philo, now_ms, ACTION_DIED), NULL);
	}
	philosopher_lifecycle(philo);
	pthread_join(supervisor_thread, NULL);
	return (NULL);
}

int	threads_loop(t_program *program)
{
	int	i;
	int	ret;

	i = 0;
	while (i < program->num_of_philos)
	{
		ret = pthread_create(&program->philos[i].thread, NULL, routine,
				&program->philos[i]);
		if (ret != 0)
			return (error(THEAD_ERR, program));
		i++;
	}
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (error(JOIN_ERR, program));
		i++;
	}
	return (0);
}
