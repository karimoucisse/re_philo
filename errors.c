/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:59:55 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/27 00:31:50 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_printer(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

void	clean_prog(t_prog *prog, int status)
{
	int	i;

	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->print_lock);
	if (!prog->philo)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < prog->nb_of_philo)
	{
		if (prog->forks)
			pthread_mutex_destroy(&(prog->forks[i]));
		pthread_mutex_destroy(&(prog->philo[i].eat_lock));
	}
	exit(status);
}
