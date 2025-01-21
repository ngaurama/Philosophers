/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:07:24 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/16 17:45:48 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_simulation
{
	int				num_phi;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				simul_over;
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
}					t_philo;

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (!philo->simulation->simul_over)
	{
		printf("%ld %d %s\n", get_time() - philo->simulation->start_time,
			philo->id, message);
	}
	pthread_mutex_unlock(&philo->simulation->print_mutex);
}

int	check_all_ate(t_simulation *sim)
{
	int	i;

	if (sim->num_must_eat == -1)
		return (0);
	i = 0;
	while (i < sim->num_phi)
	{
		pthread_mutex_lock(&sim->philosophers[i].times_eaten_mutex);
		if (sim->philosophers[i].times_eaten <= sim->num_must_eat)
		{
			pthread_mutex_unlock(&sim->philosophers[i].times_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->philosophers[i].times_eaten_mutex);
		i++;
	}
	return (1);
}

// void	*routine(void *arg)
// {
// 	t_philo			*philo;
// 	t_simulation	*sim;

// 	philo = (t_philo *)arg;
// 	sim = philo->simulation;
// 	// if (philo->id % 2 == 1)
// 	// 	usleep(15000);
// 	while (!sim->simul_over)
// 	{
// 		if (philo->id % 2 == 0)
// 		{
// 			pthread_mutex_lock(&philo->right_fork->mutex);
// 			print_log(philo, "has taken a fork");
// 			pthread_mutex_lock(&philo->left_fork->mutex);
// 			print_log(philo, "has taken a fork");
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&philo->left_fork->mutex);
// 			print_log(philo, "has taken a fork");
// 			pthread_mutex_lock(&philo->right_fork->mutex);
// 			print_log(philo, "has taken a fork");
// 		}
// 		print_log(philo, "is eating");
// 		pthread_mutex_lock(&sim->print_mutex);
// 		pthread_mutex_lock(&philo->meal_time_mutex);
// 		philo->last_meal_time = get_time();
// 		pthread_mutex_unlock(&philo->meal_time_mutex);
// 		philo->times_eaten++;
// 		pthread_mutex_unlock(&sim->print_mutex);
// 		usleep(sim->time_eat * 1000);
// 		pthread_mutex_unlock(&philo->right_fork->mutex);
// 		pthread_mutex_unlock(&philo->left_fork->mutex);
// 		pthread_mutex_lock(&sim->print_mutex);
// 		if (check_all_ate(sim))
// 			sim->simul_over = 1;
// 		pthread_mutex_unlock(&sim->print_mutex);
// 		print_log(philo, "is_sleeping");
// 		usleep(sim->time_sleep * 1000);
// 		print_log(philo, "is thinking");
// 	}
// 	return (NULL);
// }

void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*sim;

	philo = (t_philo *)arg;
	sim = philo->simulation;
	if (philo->id % 2 == 1)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&sim->print_mutex);
		if (sim->simul_over)
		{
			pthread_mutex_unlock(&sim->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->print_mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->last_meal_time = get_time();
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->meal_time_mutex);
		usleep(sim->time_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_lock(&sim->print_mutex);
		if (check_all_ate(sim))
			sim->simul_over = 1;
		pthread_mutex_unlock(&sim->print_mutex);
		print_log(philo, "is sleeping");
		usleep(sim->time_sleep * 1000);
		print_log(philo, "is thinking");
	}
	return (NULL);
}

// void	*monitor_routine(void *arg)
// {
// 	t_simulation	*sim;
// 	int				i;
// 	long			time_since_ate;

// 	sim = (t_simulation *)arg;
// 	while (!sim->simul_over)
// 	{
// 		i = 0;
// 		while (i < sim->num_phi)
// 		{
// 			pthread_mutex_lock(&sim->philosophers[i].meal_time_mutex);
// 			time_since_ate = get_time() - sim->philosophers[i].last_meal_time;
// 			if (time_since_ate > sim->time_die)
// 			{
// 				sim->simul_over = 1;
// 				print_log(&sim->philosophers[i], "died");
// 				pthread_mutex_unlock(&sim->philosophers[i].meal_time_mutex);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&sim->philosophers[i].meal_time_mutex);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->print_mutex);
		if (sim->simul_over)
		{
			pthread_mutex_unlock(&sim->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->print_mutex);
		for (int i = 0; i < sim->num_phi; i++)
		{
			pthread_mutex_lock(&sim->philosophers[i].meal_time_mutex);
			if (get_time()
				- sim->philosophers[i].last_meal_time > sim->time_die)
			{
				pthread_mutex_lock(&sim->print_mutex);
				sim->simul_over = 1;
				pthread_mutex_unlock(&sim->print_mutex);
				print_log(&sim->philosophers[i], "died");
				pthread_mutex_unlock(&sim->philosophers[i].meal_time_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&sim->philosophers[i].meal_time_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_phi time_die time_eat time_sleep [num_must_eat]\n");
		return (1);
	}

	t_simulation sim;
	sim.num_phi = atoi(argv[1]);
	sim.time_die = atoi(argv[2]);
	sim.time_eat = atoi(argv[3]);
	sim.time_sleep = atoi(argv[4]);
	sim.num_must_eat = (argc == 6) ? atoi(argv[5]) : -1;
	sim.simul_over = 0;

	if (sim.num_phi <= 0 || sim.time_die <= 0 || sim.time_eat <= 0
		|| sim.time_sleep <= 0 || (argc == 6 && sim.num_must_eat <= 0))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}

	sim.start_time = get_time();
	pthread_mutex_init(&sim.print_mutex, NULL);
	sim.forks = malloc(sizeof(t_fork) * sim.num_phi);
	sim.philosophers = malloc(sizeof(t_philo) * sim.num_phi);

	for (int i = 0; i < sim.num_phi; i++)
		pthread_mutex_init(&sim.forks[i].mutex, NULL);
	for (int i = 0; i < sim.num_phi; i++)
	{
		sim.philosophers[i].id = i + 1;
		sim.philosophers[i].times_eaten = 0;
		sim.philosophers[i].last_meal_time = sim.start_time;
		pthread_mutex_init(&sim.philosophers[i].meal_time_mutex, NULL);
		pthread_mutex_init(&sim.philosophers[i].times_eaten_mutex, NULL);
		sim.philosophers[i].left_fork = &sim.forks[i];
		sim.philosophers[i].right_fork = &sim.forks[(i + 1) % sim.num_phi];
		sim.philosophers[i].simulation = &sim;
	}

	if (sim.num_phi == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(sim.time_die * 1000);
		printf("%d 1 died\n", sim.time_die);
		return (0);
	}
	pthread_t *threads = malloc(sizeof(pthread_t) * sim.num_phi);
	for (int i = 0; i < sim.num_phi; i++)
	{
		if (pthread_create(&threads[i], NULL, routine,
				&sim.philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i
				+ 1);
			return (1);
		}
	}
	pthread_t monitor_thread;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &sim) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	for (int i = 0; i < sim.num_phi; i++)
		pthread_join(threads[i], NULL);
	pthread_join(monitor_thread, NULL);
	for (int i = 0; i < sim.num_phi; i++)
	{
		pthread_mutex_destroy(&sim.forks[i].mutex);
		pthread_mutex_destroy(&sim.philosophers[i].meal_time_mutex);
		pthread_mutex_destroy(&sim.philosophers[i].times_eaten_mutex);
	}
	pthread_mutex_destroy(&sim.print_mutex);
	free(sim.forks);
	free(sim.philosophers);
	free(threads);
	return (0);
}