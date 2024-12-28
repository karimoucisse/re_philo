/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:59:55 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/28 02:40:53 by kcisse           ###   ########.fr       */
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
	if (!prog->philos)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < prog->nb_of_philo)
	{
		if (prog->forks_locks)
			pthread_mutex_destroy(&(prog->forks_locks[i]));
		pthread_mutex_destroy(&(prog->philos[i].eat_lock));
	}
	exit(status);
}
