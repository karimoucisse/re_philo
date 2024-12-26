/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:52:00 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/27 00:39:25 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_prog prog;
	t_philo philo[200];
	pthread_mutex_t forks[200];

	check_args(ac, av);
	if (!init_struct(av, &prog, philo, forks))
		clean_prog(&prog, EXIT_FAILURE);
	start_prog(&prog);
	monitoring(&prog);
	end_prog(&prog);
	clean_prog(&prog, EXIT_FAILURE);
}
