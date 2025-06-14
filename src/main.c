/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:52:08 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 13:10:48 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"

static int	case_one(t_program *program)
{
	t_philo	philo;
	size_t	now_ms;

	philo = program->philos[0];
	pthread_mutex_lock(philo.r_fork);
	now_ms = get_current_time() - program->start_time;
	state_change_printer(&philo, now_ms, ACTION_TAKE_FORK);
	ft_usleep(program->time_to_die);
	now_ms = get_current_time() - program->start_time;
	state_change_printer(&philo, now_ms, ACTION_DIED);
	pthread_mutex_unlock(philo.r_fork);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

	program.start_time = get_current_time();
	if (argc < 5 || argc > 6)
		return (printf("Error: number of arguments incorrect\n"), 1);
	if (!input_checker(argc, argv))
		return (1);
	if (!init(&program, argv, argc))
		return (printf("Error: Initialization failed\n"), 1);
	if (program.num_of_philos == 1)
	{
		case_one(&program);
		free_resources(&program);
		return (0);
	}
	if (threads_loop(&program) != 0)
		return (printf("Error: Thread loop failed\n"), 1);
	free_resources(&program);
	return (0);
}
