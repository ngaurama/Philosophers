/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:01:28 by ngaurama          #+#    #+#             */
/*   Updated: 2025/03/08 15:41:28 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void failed_thread(int i, t_simulation *simulation, int choice)
{
	int j;
	
	j = 0;
	if (choice == 1)
		printf("Error: Failed to create philosopher thread\n");
	else
		printf("Error: Failed to create monitor thread\n");
	while (j < i)
	{
		pthread_join(simulation->philosophers[j].thread, NULL);
		j++;
	}
}

int	start_threads(t_simulation *simulation)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < simulation->num_phi)
	{
		if (pthread_create(&(simulation->philosophers[i].thread), NULL,
				philosopher_routine, &simulation->philosophers[i]))
		{
			failed_thread(i, simulation, 1);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_simulation, simulation))
	{
		failed_thread(simulation->num_phi, simulation, 2);
		return (1);
	}
	i = -1;
	while (++i < simulation->num_phi)
		pthread_join(simulation->philosophers[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
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

int	single_philo(t_simulation *simulation)
{
	print_simulation_details(simulation);
	printf("0 1 is thinking\n");
	printf(CYN "0 1 has taken the only fork\n" RESET);
	usleep(simulation->time_die * 100);
	printf(REDB "%d 1 died" RESET "\n", simulation->time_die);
	print_summary(simulation, 1);
	return (0);
}
