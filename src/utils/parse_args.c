/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:12:38 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/26 11:58:37 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
	{
		printf("Error: Invalid number_of_philosophers '%s'\n", argv[1]);
		return (0);
	}
	else if (ft_atoi(argv[1]) > 200)
	{
		printf("Error: number_of_philosophers can not be higher than 200\n");
		return (0);
	}
	if (!is_positive_integer(argv[2]))
	{
		printf("Error: Invalid time_to_die '%s'\n", argv[2]);
		return (0);
	}
	if (!is_positive_integer(argv[3]))
	{
		printf("Error: Invalid time_to_eat '%s'\n", argv[3]);
		return (0);
	}
	if (!is_positive_integer(argv[4]))
	{
		printf("Error: Invalid time_to_sleep '%s'\n", argv[4]);
		return (0);
	}
	if (argc == 6)
	{
		if (!is_positive_integer(argv[5]))
		{
			printf("Error: Invalid number_of_times_each_philosopher_must_eat '%s'\n",
				argv[5]);
			return (0);
		}
	}
	return (1);
}
