/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:39:53 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 17:12:40 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_input(char **argv, int argc, t_simulation *simulation)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_phi time_die");
		printf("time_eat time_sleep [num_must_eat]\n");
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
		printf("Error: Invalid arguments\n");
		return (0);
	}
	pthread_mutex_init(&simulation->print_mutex, NULL);
	return (1);
}
