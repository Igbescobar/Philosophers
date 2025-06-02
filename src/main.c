/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:52:08 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/02 10:35:26 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"

static int	case_one(t_program *program)
{
	t_philo	philo;

	philo = program->philos[0];
	program->start_time = get_current_time();
	if (pthread_create(&philo.thread, NULL, &routine, &philo))
		// return (error(THEAD_ERR, program));
		pthread_join(philo.thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		printf("Error: number_of_philosophers time_to_die time_to_eat time_to_sleep[number_of_times_must_eat]\n");
		return (1);
	}
	if (!input_checker(argc, argv))
		return (1);
	if (!init(&program, argv, argc))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (program.num_of_philos == 1)
		return (case_one(&program));
	if (threads_loop(&program) != 0)
	{
		printf("Error: Thread loop failed\n");
		return (1);
	}
	// Free resources
	return (0);
}
