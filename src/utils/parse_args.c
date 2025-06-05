/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:12:38 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 10:54:37 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include "../../includes/utils.h"

static int	is_positive_integer(const char *str)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > SIZE_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	input_checker(int argc, char **argv)
{
	if (!is_positive_integer(argv[1]))
		return (printf("Error: Invalid number_of_philosophers '%s'\n", argv[1]),
			0);
	if (ft_atoi(argv[1]) > 200)
		return (printf("Error: numb_of_philos can't be higher than 200\n"), 0);
	if (!is_positive_integer(argv[2]))
		return (printf("Error: Invalid time_to_die '%s'\n", argv[2]), 0);
	if (!is_positive_integer(argv[3]))
		return (printf("Error: Invalid time_to_eat '%s'\n", argv[3]), 0);
	if (!is_positive_integer(argv[4]))
		return (printf("Error: Invalid time_to_sleep '%s'\n", argv[4]), 0);
	if (argc == 6 && !is_positive_integer(argv[5]))
		return (printf("Error: Invalid numb_of_times_philo_must_eat '%s'\n",
				argv[5]), 0);
	return (1);
}
