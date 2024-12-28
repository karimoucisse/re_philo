/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:17:15 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/28 01:18:47 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	long int	time;

	if (!stop_prog(philo))
	{
		time = get_time() - philo->prog->start;
		pthread_mutex_lock(&philo->prog->print_lock);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->prog->print_lock);
	}
}

long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_usleep(time_t time, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start <= (time / 1000)))
	{
		if(stop_prog(philo))
			break ;
		usleep(100);
	}
}

