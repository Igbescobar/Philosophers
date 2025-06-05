/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:49:37 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 13:10:45 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

void	state_change_printer(t_philo *philo, size_t timestamp,
		const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%zu %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}

int	error(char *str, t_program *program)
{
	pthread_mutex_lock(&program->write_lock);
	printf("%s\n", str);
	pthread_mutex_unlock(&program->write_lock);
	return (1);
}
