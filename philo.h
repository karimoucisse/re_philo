/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:47:54 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/27 00:50:04 by kcisse           ###   ########.fr       */
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
#include "./utils/utils.h"

struct s_prog;
typedef struct s_philo
{
	int				id;
	int				nb_of_philo;
	int				eat_bool;
	int				think_bool;
	int				sleep_bool;
	int				eaten;
	int				eat_nrb_time;
	long int		time;
	long int		last_meal;
	long int		start;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	eat_lock;
	pthread_t		p_thread;
	struct s_prog	*prog;
}					t_philo;

typedef struct s_prog
{
	int				nb_of_philo;
	int				is_dead;
	long int		start;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philo;
}	t_prog;

// CHECKER
int		check_args(int ac, char **av);

// ERRORS
void	error_printer(char *msg);
void	clean_prog(t_prog *prog, int status);

// INIT
int		init_struct(char **av, t_prog *m, t_philo *p,
						pthread_mutex_t *f);
// ROUTINE
void	*routine(void *data);

#endif
