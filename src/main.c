/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:52:08 by igngonza          #+#    #+#             */
/*   Updated: 2025/07/29 16:58:23 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
		return (printf("Error: number of arguments incorrect\n"), 1);
	if (!input_checker(argc, argv))
		return (1);
	if (!init(&program, argv, argc))
		return (printf("Error: Initialization failed\n"), 1);
	program.start_time = get_current_time();
	if (threads_loop(&program) != 0)
		return (printf("Error: Thread loop failed\n"), 1);
	free_resources(&program);
	return (0);
}
