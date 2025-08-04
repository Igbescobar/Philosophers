/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:48:12 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/02 20:46:32 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	philosopher_lifecycle(philo);
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
