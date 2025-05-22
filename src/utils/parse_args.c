/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:12:38 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 11:53:14 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_args.h"

static int	parse_positive_int(const char *str, int *out)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	*out = (int)result;
	return (1);
}

int	parse_arguments(int argc, char **argv, int *number_of_philosophers,
		int *time_to_die, int *time_to_eat, int *time_to_sleep,
		int *number_of_times_each_philosopher_must_eat)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage:%s number_of_philosophers time_to_die time_to_eat time_to_sleep[number_of_times_must_eat]\n ",
			argv[0]);
		return (0);
	}
	if (!parse_positive_int(argv[1], number_of_philosophers))
	{
		printf("Error: Invalid number_of_philosophers '%s'\n", argv[1]);
		return (0);
	}
	else if (*number_of_philosophers > 200)
	{
		printf("Error: number_of_philosophers can not be higher than 200");
		return (0);
	}
	if (!parse_positive_int(argv[2], time_to_die))
	{
		printf("Error: Invalid time_to_die '%s'\n", argv[2]);
		return (0);
	}
	if (!parse_positive_int(argv[3], time_to_eat))
	{
		printf("Error: Invalid time_to_eat '%s'\n", argv[3]);
		return (0);
	}
	if (!parse_positive_int(argv[4], time_to_sleep))
	{
		printf("Error: Invalid time_to_sleep '%s'\n", argv[4]);
		return (0);
	}
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5],
				number_of_times_each_philosopher_must_eat))
		{
			printf("Error: Invalid number_of_times_each_philosopher_must_eat '%s'\n",
				argv[5]);
			return (0);
		}
	}
	else
	{
		*number_of_times_each_philosopher_must_eat = -1;
	}
	if (*number_of_philosophers < 1)
	{
		printf("Error: number_of_philosophers must be at least 1\n");
		return (0);
	}
	if (*time_to_die < 1 || *time_to_eat < 1 || *time_to_sleep < 1)
	{
		printf("Error: time_to_die,time_to_eat and time_to_sleep must be at least 1 ms\n");
		return (0);
	}
	if (argc == 6 && *number_of_times_each_philosopher_must_eat < 0)
	{
		printf("Error: number_of_times_each_philosopher_must_eat must be at least 0\n");
		return (0);
	}
	return (1);
}
