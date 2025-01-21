/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:55:32 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 20:13:31 by ngaurama         ###   ########.fr       */
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
	pthread_mutex_destroy(&simulation->simul_over_mutex);
	free(simulation->forks);
	free(simulation->philosophers);
}

void	print_intro(void)
{
	printf("%s\n", BLU "\n==============================================");
	printf("%s\n", BMAG "WELCOME TO THE DINING PHILOSOPHERS SIMULATION!");
	printf("%s\n", BLU "==============================================");
	printf("%s\n", reset);
}

void	print_summary(t_simulation *simulation)
{
	printf("%s\n", BYEL "\nSIMULATION SUMMARY:");
	printf("%s\n", BGRN "=================================");
	for (int i = 0; i < simulation->num_phi; i++)
	{
		printf("%sPhilosopher %d ate %d times.%s\n", BGRN,
			simulation->philosophers[i].id,
			simulation->philosophers[i].times_eaten, reset);
	}
	printf("%sSimulation ended after %ldms.%s\n", BRED, get_time()
		- simulation->start_time, reset);
	printf("%s\n", BGRN "=================================");
}

void	print_simulation_details(t_simulation *simulation)
{
	printf("%sDetails of the simulation:\n%s", CYN, reset);
	printf("%s- Number of philosophers and forks: %d\n", BYEL, simulation->num_phi);
	printf("%s- Time to die: %d ms\n", BYEL, simulation->time_die);
	printf("- Time to eat: %d ms\n", simulation->time_eat);
	printf("- Time to sleep: %d ms\n", simulation->time_sleep);
	if (simulation->num_must_eat > 0)
	{
		printf("- Number of times each philosopher must eat: %d%s\n",
			simulation->num_must_eat, reset);
	}
	else
	{
		printf("- Number of times each philosopher must eat: Not specified%s\n",
			reset);
	}
	printf("%sStarting simulation...%s\n", GRN, reset);
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	print_intro();
	if (!init_input(argv, argc, &simulation))
		return (1);
	print_simulation_details(&simulation);
	sleep(2);
	if (!init_philo(&simulation))
		return (1);
	start_threads(&simulation);
	printf("%sSimulation complete!%s\n", BGRN, reset);
	print_summary(&simulation);
	cleanup_simulation(&simulation);
	return (0);
}
