/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:52:08 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/28 11:05:42 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_args.h"
#include "../includes/philo.h"

static int	case_one(t_program *program)
{
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		printf("Error: number_of_philosophers time_to_die time_to_eat time_to_sleep[number_of_times_must_eat]\n ");
		return (1);
	}
	if (input_checker(argc, argv))
		return (1);
	if (init(&program, argv, argc))
		return (1);
	if (program.num_of_philos == 1)
		return (case_one(&program));
	// if (thread_init(&data))
	//	return (1);
	// ft_exit(&data);
	return (0);
}
