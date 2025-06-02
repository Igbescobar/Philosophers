/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:48:12 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/02 11:09:18 by igngonza         ###   ########.fr       */
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

static int	philo_get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->meal_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
	return (meals);
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
		pthread_mutex_lock(&philo->program->dead_lock);
		if (get_current_time()
			- philo->last_meal_time > philo->program->time_to_die)
		{
			philo->program->dead_flag = 1;
			pthread_mutex_unlock(&philo->program->dead_lock);
			state_change_printer(philo, get_current_time(), 5);
			break ;
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo		*philo;
	pthread_t	supervisor_thread;
	int			max_eats;

	philo = (t_philo *)philo_pointer;
	max_eats = philo->program->num_times_to_eat;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	philo->last_meal_time = get_current_time();
	if (pthread_create(&supervisor_thread, NULL, supervisor, philo) != 0)
	{
		state_change_printer(philo, get_current_time(), 5);
		return (NULL);
	}
	while (!philo_is_dead(philo) && (max_eats < 0
			|| philo_get_meals(philo) < max_eats))
	{
		eating_process(philo);
		if (philo_is_dead(philo))
			break ;
		state_change_printer(philo, get_current_time(), 4);
		ft_usleep(philo->time_to_sleep);
		if (philo_is_dead(philo))
			break ;
		state_change_printer(philo, get_current_time(), 4);
	}
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->dead = 1;
	pthread_mutex_unlock(&philo->program->dead_lock);
	pthread_join(supervisor_thread, NULL);
	return (NULL);
}

int	threads_loop(t_program *program)
{
	int	i;
	int	ret;

	program->start_time = get_current_time();
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
