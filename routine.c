/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:40:01 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/28 01:26:35 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->prog->nb_of_philo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
		usleep(philo->prog->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (philo->id % 2)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_msg(philo, "has taken a fork");
}

void	eat_sleep_routine(t_philo *philo)
{
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	ft_usleep(philo->prog->time_to_eat, philo);
	if (!stop_prog(philo))
	{
		pthread_mutex_lock(&philo->eat_lock);
		philo->nbr_of_time_ate += 1;
		pthread_mutex_unlock(&philo->eat_lock);
	}
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	print_msg(philo, "is sleeping");
	ft_usleep(philo->prog->time_to_sleep, philo);
}

int stop_prog(t_philo *philo)
{
	int res;

	res = 0;
	pthread_mutex_lock(&philo->prog->dead_lock);
	if(philo->prog->is_dead)
		res = 1;
	pthread_mutex_lock(&philo->prog->dead_lock);
	return (res);
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = (t_prog *)philo->prog;
	if ((prog->nb_of_philo % 2) && philo->id == 1)
		usleep(10);
	else if (!(philo->id % 2))
		ft_usleep((prog->time_to_eat / 2), philo);
	while (!stop_prog(philo))
	{
		take_forks(philo);
		if (prog->nb_of_philo == 1)
			break ;
		eat_sleep_routine(philo);
		print_msg(philo, "is thinking");
		if (philo->prog->nb_of_philo % 2
			&& philo->prog->time_to_eat > philo->prog->time_to_sleep)
			usleep((philo->prog->time_to_die - (philo->prog->time_to_eat
						+ philo->prog->time_to_sleep)) / 2);
		else if (philo->prog->time_to_eat == philo->prog->time_to_sleep)
			usleep(500);
	}
	return (0);
}
