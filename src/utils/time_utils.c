/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:20:14 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 16:16:28 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/time.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (size_t)(tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

// int	ft_usleep(size_t milliseconds)
//{
//	size_t start;

//	start = get_current_time();
//	while ((get_current_time() - start) < milliseconds)
//		usleep(500);
//	return (0);
//}