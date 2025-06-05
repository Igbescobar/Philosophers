/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:57:01 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 10:57:32 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	counter;

	i = 0;
	sign = 1;
	result = 0;
	counter = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	while ((str[i] == '-' || str[i] == 43) && (counter < 1))
	{
		if (str[i] == '-')
			sign *= -1;
		counter = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)(tv.tv_sec * 1000UL + tv.tv_usec / 1000UL));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	free_resources(t_program *program)
{
	int	i;

	if (program->philos)
		free(program->philos);
	if (program->forks)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks);
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}
