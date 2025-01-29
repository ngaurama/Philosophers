# include "../ansi_colors.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
}					t_fork;

typedef struct s_simulation
{
	int				num_phi;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				simul_over;
	pthread_mutex_t	simul_over_mutex;
	long			start_time;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	struct s_philo	*philosophers;
}					t_simulation;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	times_eaten_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_simulation	*simulation;
	pthread_t		thread;
}					t_philo;

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long duration_ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < duration_ms)
		usleep(100);
}

int	init_input(char **argv, int argc, t_simulation *simulation)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf("%sUsage: ./philo num_phi time_die", BRED);
		ft_printf("time_eat time_sleep [num_must_eat]%s\n\n", RESET);
		return (0);
	}
	simulation->num_phi = atoi(argv[1]);
	simulation->time_die = atoi(argv[2]);
	simulation->time_eat = atoi(argv[3]);
	simulation->time_sleep = atoi(argv[4]);
	if (argc == 6)
		simulation->num_must_eat = atoi(argv[5]);
	else
		simulation->num_must_eat = -1;
	simulation->simul_over = 0;
	if (simulation->num_phi <= 0 || simulation->time_die <= 0
		|| simulation->time_eat <= 0 || simulation->time_sleep <= 0
		|| (argc == 6 && simulation->num_must_eat <= 0))
	{
		ft_printf("Error: Invalid arguments\n");
		return (0);
	}
	pthread_mutex_init(&simulation->print_mutex, NULL);
    pthread_mutex_init(&simulation->simul_over_mutex, NULL);
	return (1);
}


int	is_simulation_over(t_philo *philo)
{
	int	over;

	pthread_mutex_lock(&philo->simulation->simul_over_mutex);
	over = philo->simulation->simul_over;
	pthread_mutex_unlock(&philo->simulation->simul_over_mutex);
	return (over);
}

void	log_action(t_philo *philo, const char *action, char *color)
{
	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (!is_simulation_over(philo))
		ft_printf("%s%ld %d %s%s\n", color, get_time()
			- philo->simulation->start_time, philo->id, action, RESET);
	pthread_mutex_unlock(&philo->simulation->print_mutex);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking", WHT);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork", CYN);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_action(philo, "is eating", GRNB);
	precise_sleep(philo->simulation->time_eat);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	sleep_philo(t_philo *philo)
{
	log_action(philo, "is sleeping", MAG);
	precise_sleep(philo->simulation->time_sleep);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (is_simulation_over(philo))
            break;
        think(philo);
        if (is_simulation_over(philo))
            break;
        pick_up_forks(philo);
        if (is_simulation_over(philo))
        {
            put_down_forks(philo);
            break;
        }
        eat(philo);
        put_down_forks(philo);
        if (is_simulation_over(philo))
            break;
        sleep_philo(philo);
    }
    return (NULL);
}

void	*monitor_philosopher(t_simulation *simulation, int i,
		int *all_satisfied)
{
	long	current_time;
	long	last_meal;

	pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
	current_time = get_time();
	last_meal = simulation->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
	if (current_time - last_meal > simulation->time_die)
	{
		log_action(&simulation->philosophers[i], "died", REDB);
		pthread_mutex_lock(&simulation->simul_over_mutex);
		simulation->simul_over = 1;
		pthread_mutex_unlock(&simulation->simul_over_mutex);
	}
	if (simulation->num_must_eat > 0)
	{
		pthread_mutex_lock(&simulation->philosophers[i].times_eaten_mutex);
		if (simulation->philosophers[i].times_eaten < simulation->num_must_eat)
			*all_satisfied = 0;
		pthread_mutex_unlock(&simulation->philosophers[i].times_eaten_mutex);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	t_simulation	*simulation;
	int				i;
	int				all_satisfied;

	simulation = (t_simulation *)arg;
	while (!simulation->simul_over)
	{
		all_satisfied = 1;
		i = 0;
		while (i < simulation->num_phi)
		{
			monitor_philosopher(simulation, i, &all_satisfied);
			i++;
		}
		if (simulation->num_must_eat > 0 && all_satisfied)
		{
			pthread_mutex_lock(&simulation->simul_over_mutex);
			simulation->simul_over = 1;
			pthread_mutex_unlock(&simulation->simul_over_mutex);
		}
		usleep(500);
	}
	return (NULL);
}

void	start_threads(t_simulation *simulation)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < simulation->num_phi)
	{
		if (pthread_create(&(simulation->philosophers[i].thread), NULL,
				philosopher_routine, &simulation->philosophers[i]))
		{
			ft_printf("Error: Failed to create philosopher thread\n");
			exit(1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, simulation))
	{
		ft_printf("Error: Failed to create monitor thread\n");
		exit(1);
	}
	i = -1;
	while (++i < simulation->num_phi)
		pthread_join(simulation->philosophers[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
}

void	cleanup_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_phi)
	{
		pthread_mutex_destroy(&simulation->forks[i].mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].meal_time_mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].times_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->simul_over_mutex);
	free(simulation->forks);
	free(simulation->philosophers);
}

int	init_forks(t_simulation *simul)
{
	int	i;

	simul->forks = malloc(sizeof(t_fork) * simul->num_phi);
	if (!simul->forks)
		return (0);
	i = -1;
	while (++i < simul->num_phi)
		pthread_mutex_init(&simul->forks[i].mutex, NULL);
	return (1);
}

int	init_philosophers(t_simulation *simul)
{
	int	i;

	simul->philosophers = malloc(sizeof(t_philo) * simul->num_phi);
	if (!simul->philosophers)
		return (free(simul->forks), 0);
	i = -1;
	simul->start_time = get_time();
	while (++i < simul->num_phi)
	{
		simul->philosophers[i].id = i + 1;
		simul->philosophers[i].times_eaten = 0;
		simul->philosophers[i].last_meal_time = simul->start_time;
		pthread_mutex_init(&simul->philosophers[i].meal_time_mutex, NULL);
		pthread_mutex_init(&simul->philosophers[i].times_eaten_mutex, NULL);
		simul->philosophers[i].left_fork = &simul->forks[i];
		simul->philosophers[i].right_fork = &simul->forks[(i + 1)
			% simul->num_phi];
		simul->philosophers[i].simulation = simul;
	}
	return (1);
}

int	init_philo(t_simulation *simul)
{
	if (!init_forks(simul))
		return (0);
	if (!init_philosophers(simul))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!init_input(argv, argc, &simulation))
		return (1);
	if (!init_philo(&simulation))
		return (1);
	start_threads(&simulation);
	cleanup_simulation(&simulation);
	return (0);
}