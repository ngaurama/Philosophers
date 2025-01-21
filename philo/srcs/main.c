/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:55:32 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 17:03:58 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			printf("Error: Failed to create philosopher thread\n");
			exit(1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, simulation))
	{
		printf("Error: Failed to create monitor thread\n");
		exit(1);
	}
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
	free(simulation->forks);
	free(simulation->philosophers);
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
