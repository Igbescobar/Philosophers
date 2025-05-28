/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:26:40 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 15:19:07 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include <stddef.h>
# include <sys/time.h>

size_t	get_current_time(void);

#endif