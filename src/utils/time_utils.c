/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:20:14 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 12:29:00 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "../../includes/time.h"

size_t	get_timestamp_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (size_t)(tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}