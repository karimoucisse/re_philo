#include "philo.h"

int	init_prog(char **av, t_prog *prog, pthread_mutex_t *forks)
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
	if (av[5])
			prog->max_eat_count = ft_atoi(av[5]);
		else
			prog->max_eat_count = -1;
	prog->is_dead = 0;
	prog->forks_locks = forks;
	// prog->philos = philos;
	return (1);
}
t_philo	*init_philo(t_prog *prog)
{
	int	i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * prog->nb_of_philo);
	i = -1;
	while (++i < prog->nb_of_philo)
	{

		if (pthread_mutex_init(&(philo)[i].eat_lock, NULL) != 0)
			return (0);
		philo->id = i + 1;
		philo->nbr_of_time_ate = 0;
		philo->last_meal = 0;
		philo->l_fork = &prog->forks_locks[i];
		philo->r_fork = &prog->forks_locks[(i + 1) % prog->nb_of_philo];
		philo->prog = prog;
	}
	return (philo);
}

t_prog	*init_struct(char **av)
{
	int	i;

	t_prog *prog;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = NULL;
	prog = malloc(sizeof(t_prog));
	if(!prog)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	i = 0;
	while (i < (ft_atoi(av[1])))
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (!init_prog(av, prog, forks))
		return (0);
	philos = init_philo(prog);
	if (!philos)
		return (0);
	prog->philos = philos;
	return (prog);
}
