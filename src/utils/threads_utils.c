/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:00:01 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 11:08:08 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

int	philo_get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(philo->meal_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
	return (meals);
}

void	philosopher_lifecycle(t_philo *philo)
{
	int		max_eats;
	size_t	now_rel;

	max_eats = philo->program->num_times_to_eat;
	while (!philo_is_dead(philo) && (max_eats < 0
			|| philo_get_meals(philo) < max_eats))
	{
		eating_process(philo);
		if (philo_is_dead(philo))
			break ;
		now_rel = get_current_time() - philo->program->start_time;
		state_change_printer(philo, now_rel, 4);
		ft_usleep(philo->time_to_sleep);
		if (philo_is_dead(philo))
			break ;
		now_rel = get_current_time() - philo->program->start_time;
		state_change_printer(philo, now_rel, 3);
	}
}

void	mark_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->program->dead_flag = 1;
	pthread_mutex_unlock(&philo->program->dead_lock);
}
