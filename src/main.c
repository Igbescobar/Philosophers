/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:52:08 by igngonza          #+#    #+#             */
/*   Updated: 2025/05/22 12:26:04 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	t_program	program;
	size_t		start_time;

	if (!parse_arguments(argc, argv, &number_of_philosophers, &time_to_die,
			&time_to_eat, &time_to_sleep,
			&number_of_times_each_philosopher_must_eat))
		return (1);
	start_time = get_timestamp_ms();
	printf("Simulation start time: %zu ms\n", start_time);
	program.dead_flag = 0;
	pthread_mutex_init(&program.dead_lock, NULL);
	pthread_mutex_init(&program.meal_lock, NULL);
	pthread_mutex_init(&program.write_lock, NULL);
	printf("All arguments valid.\n");
	return (0);
}
