/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:32:12 by igngonza          #+#    #+#             */
/*   Updated: 2025/06/05 13:11:39 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>

# define THEAD_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHEN JOINING THREADS"
void	state_change_printer(t_philo *philo, size_t timestamp,
			const char *action);
int		ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_strcmp(char *s1, char *s2);
int		ft_usleep(size_t milliseconds);
int		error(char *str, t_program *program);

#endif