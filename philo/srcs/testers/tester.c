#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

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
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	precise_sleep(long duration_ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < duration_ms)
	{
		usleep(100);
	}
}

int	init_input(char **argv, int argc, t_simulation *simulation)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf("Usage: ./philo num_phi time_die time_eat time_sleep [num_must_eat]\n");
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

void	log_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (!is_simulation_over(philo))
		ft_printf("%ld %d %s\n", get_time() - philo->simulation->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->simulation->print_mutex);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_action(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	log_action(philo, "is eating");
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
	log_action(philo, "is sleeping");
	precise_sleep(philo->simulation->time_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_simulation_over(philo))
			break ;
		think(philo);
		if (is_simulation_over(philo))
			break ;
		pick_up_forks(philo);
		if (is_simulation_over(philo))
		{
			put_down_forks(philo);
			break ;
		}
		eat(philo);
		put_down_forks(philo);
		if (is_simulation_over(philo))
			break ;
		sleep_philo(philo);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	t_simulation	*simulation;
	int				i;
	long			current_time;
	int				all_satisfied;
	long			last_meal;

	simulation = (t_simulation *)arg;
	while (!simulation->simul_over)
	{
		all_satisfied = 1;
		for (i = 0; i < simulation->num_phi; i++)
		{
			pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
			current_time = get_time();
			last_meal = simulation->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
			if (current_time - last_meal > simulation->time_die)
			{
				log_action(&simulation->philosophers[i], "died");
				pthread_mutex_lock(&simulation->simul_over_mutex);
				simulation->simul_over = 1;
				pthread_mutex_unlock(&simulation->simul_over_mutex);
			}
			if (simulation->num_must_eat > 0)
			{
				pthread_mutex_lock(&simulation->philosophers[i].times_eaten_mutex);
				if (simulation->philosophers[i].times_eaten < simulation->num_must_eat)
					all_satisfied = 0;
				pthread_mutex_unlock(&simulation->philosophers[i].times_eaten_mutex);
			}
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
	pthread_t	monitor_thread;

	for (int i = 0; i < simulation->num_phi; i++)
	{
		if (pthread_create(&(simulation->philosophers[i].thread), NULL,
				philosopher_routine, &simulation->philosophers[i]))
		{
			ft_printf("Error: Failed to create philosopher thread\n");
			exit(1);
		}
	}
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, simulation))
	{
		ft_printf("Error: Failed to create monitor thread\n");
		exit(1);
	}
	for (int i = 0; i < simulation->num_phi; i++)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
	}
	pthread_join(monitor_thread, NULL);
}

void	cleanup_simulation(t_simulation *simulation)
{
	for (int i = 0; i < simulation->num_phi; i++)
	{
		pthread_mutex_destroy(&simulation->forks[i].mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].meal_time_mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].times_eaten_mutex);
	}
	pthread_mutex_destroy(&simulation->print_mutex);
    pthread_mutex_destroy(&simulation->simul_over_mutex);
	free(simulation->forks);
	free(simulation->philosophers);
}

int	init_philo(t_simulation *simulation)
{
	simulation->forks = malloc(sizeof(t_fork) * simulation->num_phi);
	if (!simulation->forks)
		return (0);
	simulation->philosophers = malloc(sizeof(t_philo) * simulation->num_phi);
	if (!simulation->philosophers)
	{
		free(simulation->forks);
		return (0);
	}
	for (int i = 0; i < simulation->num_phi; i++)
	{
		pthread_mutex_init(&simulation->forks[i].mutex, NULL);
	}
	simulation->start_time = get_time();
	for (int i = 0; i < simulation->num_phi; i++)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].times_eaten = 0;
		simulation->philosophers[i].last_meal_time = simulation->start_time;
		pthread_mutex_init(&simulation->philosophers[i].meal_time_mutex, NULL);
		pthread_mutex_init(&simulation->philosophers[i].times_eaten_mutex,
			NULL);
		simulation->philosophers[i].left_fork = &simulation->forks[i];
		simulation->philosophers[i].right_fork = &simulation->forks[(i + 1)
			% simulation->num_phi];
		simulation->philosophers[i].simulation = simulation;
	}
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
