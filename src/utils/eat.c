/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:25:01 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/02 11:40:15 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

static int	take_forks_even(t_philo *p)
{
	pthread_mutex_lock(p->r_fork);
	if (philo_is_dead(p))
	{
		pthread_mutex_unlock(p->r_fork);
		return (0);
	}
	state_change_printer(p, get_current_time(), 1);
	pthread_mutex_lock(p->l_fork);
	if (philo_is_dead(p))
	{
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		return (0);
	}
	state_change_printer(p, get_current_time(), 1);
	return (1);
}

static int	take_forks_odd(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	if (philo_is_dead(p))
	{
		pthread_mutex_unlock(p->l_fork);
		return (0);
	}
	state_change_printer(p, get_current_time(), 1);
	pthread_mutex_lock(p->r_fork);
	if (philo_is_dead(p))
	{
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(p->l_fork);
		return (0);
	}
	state_change_printer(p, get_current_time(), 1);
	return (1);
}

static int	take_forks(t_philo *p)
{
	if (philo_is_dead(p))
		return (0);
	if (p->id % 2 == 0)
		return (take_forks_even(p));
	else
		return (take_forks_odd(p));
}

static void	leave_forks(t_philo *p)
{
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

void	eating_process(t_philo *philo)
{
	if (philo_is_dead(philo))
		return ;
	if (!take_forks(philo))
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	state_change_printer(philo, get_current_time(), 2);
	ft_usleep(philo->time_to_eat);
	leave_forks(philo);
}
