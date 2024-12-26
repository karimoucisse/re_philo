/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:52:00 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/27 00:46:01 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_prog(t_prog prog)
{
	int i;

	i = -1;
	while (++i < prog.nb_of_philo)
	{
		if (pthread_create(&prog.philo[i].p_thread, NULL, &routine,
				&(prog.philo[i])) != 0)
			prog_destroyer(&prog, 1);
	}
	return (1);
}
int monitoring(t_prog prog)
{

}
int end_prog(t_prog prog)
{
	int	i;

	i = -1;
	while (++i < prog.nb_of_philo)
	{
		if (pthread_join(prog.philo[i].p_thread, NULL) != 0)
			prog_destroyer(&prog, 1);
	}
	return (1);
}

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
