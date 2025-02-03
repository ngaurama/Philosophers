/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:46:06 by ngaurama          #+#    #+#             */
/*   Updated: 2025/02/03 11:51:33 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_intro(void)
{
	printf(BLU "\n==============================================\n");
	printf(BMAG "WELCOME TO THE DINING PHILOSOPHERS SIMULATION!\n");
	printf(BLU "==============================================\n");
	printf(RESET "\n");
}

void	print_summary(t_simulation *simulation, int i)
{
	int	j;

	j = -1;
	printf(BGRN "Simulation complete!\n" RESET);
	printf(BYEL "\nSIMULATION SUMMARY:\n");
	printf(BGRN "=================================\n" RESET);
	if (simulation->simul_over == 2)
	{
		while (++j < simulation->num_phi)
		{
			printf(BGRN "Philosopher %d ate %d times.\n" RESET,
				simulation->philosophers[j].id,
				simulation->philosophers[j].times_eaten);
		}
	}
	else
		printf(REDB "A philosopher died.%s\n", RESET);
	if (i == 1)
		printf("Simulation ended after %d ms.\n" RESET, simulation->time_die);
	else
		printf("Simulation ended after %ld ms.\n" RESET, get_time()
			- simulation->start_time);
	printf(BGRN "=================================\n" RESET);
}

void	print_simulation_details(t_simulation *simulation)
{
	printf(CYN "Details of the simulation:\n" RESET);
	printf(BYEL "- Number of philosophers and forks: %d\n",
		simulation->num_phi);
	printf(BYEL "- Time to die: %d ms\n- Time to eat: ", simulation->time_die);
	printf("%d ms\n- Time to sleep: %d ms\n", simulation->time_eat,
		simulation->time_sleep);
	if (simulation->num_must_eat > 0)
		printf("- Number of times each philosopher must eat: %d\n" RESET,
			simulation->num_must_eat);
	else
	{
		printf("- Number of times each philosopher must eat: ");
		printf("Not specified\n" RESET);
	}
	printf(GRN "Starting simulation...\n" RESET);
	printf("\n");
	usleep(2000000);
}
