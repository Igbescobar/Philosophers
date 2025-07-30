/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:10:33 by igngonza          #+#    #+#             */
/*   Updated: 2025/07/30 11:11:35 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

void	leave_forks(t_philo *p)
{
	if (p->program->num_of_philos == 1)
	{
		pthread_mutex_unlock(p->l_fork);
		return ;
	}
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}
