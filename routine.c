/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:40:01 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/27 00:48:40 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)data;
	prog = philo->prog;
	if ((philo->nb_of_philo % 2) && philo->id == 1)
		usleep(10);
	else if (!(philo->id % 2))
		ft_usleep((prog->time_to_eat / 2), philo);
	while (1)
	{
		
	}
	return (0);
}
