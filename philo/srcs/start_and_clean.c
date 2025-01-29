/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:01:28 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:52:27 by ngaurama         ###   ########.fr       */
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

int	single_philo(t_simulation *simulation)
{
	print_simulation_details(simulation);
	sleep(2);
	ft_printf("0 1 is thinking\n");
	ft_printf("%s0 1 has taken the only fork%s\n", CYN, RESET);
	usleep(simulation->time_die * 100);
	ft_printf("%s%d 1 died%s\n", REDB, (simulation->time_die), RESET);
	print_summary(simulation, 1);
	return (0);
}
