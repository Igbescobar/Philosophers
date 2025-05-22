/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:24:09 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 11:25:57 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARGS_H
# define PARSE_ARGS_H

# include "philo.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

int	parse_arguments(int argc, char **argv, int *number_of_philosophers,
		int *time_to_die, int *time_to_eat, int *time_to_sleep,
		int *number_of_times_each_philosopher_must_eat);

#endif