/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:52:00 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/28 03:13:37 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_prog(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nb_of_philo)
	{
		if (pthread_create(&prog->philos[i].p_thread, NULL, &routine,
				&(prog->philos[i])) != 0)
			clean_prog(prog, 1);
	}
	return (1);
}

int	ft_philo_is_dead(t_philo *philo)
{
	time_t	current_time;

	current_time = get_time();
	if(current_time - philo->last_meal > philo->prog->time_to_die)
	{
		pthread_mutex_lock(&philo->prog->dead_lock);
		philo->prog->is_dead = 1;
		pthread_mutex_unlock(&philo->prog->dead_lock);
		print_msg(philo, "died");
		return (1);
	}
	return (0);
}

int	ft_handle_conditions(t_prog *prog)
{
	int	i;
	int	nbr_full_philo;

	i = -1;
	nbr_full_philo = 0;
	while (++i < prog->nb_of_philo)
	{
		pthread_mutex_lock(&prog->philos[i].eat_lock);
		if (ft_philo_is_dead(&prog->philos[i]))
			return (1);
		if(prog->philos[i].nbr_of_time_ate == prog->max_eat_count)
			nbr_full_philo++;
		pthread_mutex_unlock(&prog->philos[i].eat_lock);
	}
	if(nbr_full_philo == prog->nb_of_philo)
		return (1);
	return (0);
}

void	monitoring(t_prog *prog)
{
	while (1)
	{
		usleep(500);
		if (ft_handle_conditions(prog))
			break ;
	}
}

int	end_prog(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nb_of_philo)
	{
		if (pthread_join(prog->philos[i].p_thread, NULL) != 0)
			clean_prog(prog, 1);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_prog			*prog;

	check_args(ac, av);
	prog = init_struct(av);
	if(!prog)
		clean_prog(prog, EXIT_FAILURE);
	int i = 0;
	while(i < prog->nb_of_philo)
	{
		printf("philo %d\n", prog->philos[i].id);
		i++;
	}
	// start_prog(prog);
	// monitoring(prog);
	// end_prog(prog);
	clean_prog(prog, EXIT_FAILURE);
}
