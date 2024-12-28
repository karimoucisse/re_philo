/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:47:54 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/28 03:12:34 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "./utils/utils.h"

struct s_prog;
typedef struct s_philo
{
	pthread_t		p_thread;
	int				id;
	int				nbr_of_time_ate;
	pthread_mutex_t	eat_lock;
	time_t			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_prog	*prog;
}	t_philo;

typedef struct s_prog
{
	time_t			start;
	int				nb_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int 			max_eat_count;
	int				is_dead;
	pthread_mutex_t	*forks_locks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}	t_prog;

// CHECKER
int		check_args(int ac, char **av);

// ERRORS
void	error_printer(char *msg);
void	clean_prog(t_prog *prog, int status);

// INIT
t_prog	*init_struct(char **av);
// ROUTINE
void	*routine(void *data);
int		stop_prog(t_philo *philo);

// UTILS
long	get_time(void);
void	print_msg(t_philo *philo, char *msg);
void	ft_usleep(time_t time, t_philo *philo);
#endif
