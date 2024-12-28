#include "philo.h"

int	init_prog(char **av, t_prog *prog, t_philo *philos, pthread_mutex_t *forks)
{
	if (pthread_mutex_init(&prog->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&prog->print_lock, NULL) != 0)
		return (0);
	prog->start = get_time();
	prog->nb_of_philo = ft_atoi(av[1]);
	prog->time_to_die = ft_atoi(av[2]) * 1000;
	prog->time_to_eat = ft_atoi(av[3]) * 1000;
	prog->time_to_sleep = ft_atoi(av[4]) * 1000;
	prog->eat_count = 0;
	prog->is_dead = 0;
	prog->forks_locks = forks;
	prog->philos = philos;
	return (1);
}
int	init_philo(char **av, t_philo *philo, t_prog *prog, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < prog->nb_of_philo)
	{
		if (av[5])
			philo->eat_nrb_time = ft_atoi(av[5]);
		else
			philo->eat_nrb_time = -1;
		if (pthread_mutex_init(&(philo)[i].eat_lock, NULL) != 0)
			return (0);
		philo->id = i + 1;
		philo->nbr_of_time_ate = 0;
		philo->last_meal = 0;
		philo->l_fork = &forks[i];
		philo->r_fork = &forks[(i + 1) % prog->nb_of_philo];
		philo->prog = prog;
	}
	return (1);
}

int	init_struct(char **av, t_prog *prog, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < (ft_atoi(av[1])))
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
	}
	if (!init_prog(av, prog, philos, forks))
		return (0);
	if (!init_philo(av, philos, prog, forks))
		return (0);
	return (1);
}
