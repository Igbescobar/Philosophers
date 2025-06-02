/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:49:37 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/30 13:10:33 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

void	state_change_printer(t_philo *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	if (action == 1)
		printf("%zu %d has taken a fork\n", timestamp, philo->id);
	if (action == 2)
		printf("%zu %d is eating\n", timestamp, philo->id);
	if (action == 3)
		printf("%zu %d is sleeping\n", timestamp, philo->id);
	if (action == 4)
		printf("%zu %d is thinking\n", timestamp, philo->id);
	if (action == 5)
		printf("%zu %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->program->write_lock);
}

int	error(char *str, t_program *program)
{
	pthread_mutex_lock(&program->write_lock);
	printf("%s\n", str);
	(void)program;
	// if (program)
	// ft_exit(program);
	pthread_mutex_unlock(&program->write_lock);
	return (1);
}
