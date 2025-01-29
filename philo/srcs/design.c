/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:46:06 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 01:09:41 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_intro(void)
{
	ft_printf("%s\n", BLU "\n==============================================");
	ft_printf("%s\n", BMAG "WELCOME TO THE DINING PHILOSOPHERS SIMULATION!");
	ft_printf("%s\n", BLU "==============================================");
	ft_printf("%s\n", RESET);
}

void	print_summary(t_simulation *simulation, int i)
{
	int	j;

	j = -1;
	ft_printf("%sSimulation complete!%s\n", BGRN, RESET);
	ft_printf("%s\n", BYEL "\nSIMULATION SUMMARY:");
	ft_printf("%s\n=================================%s\n", BGRN, RESET);
	if (simulation->simul_over == 2)
	{
		while (++j < simulation->num_phi)
		{
			ft_printf("%sPhilosopher %d ate %d times.%s\n", BGRN,
				simulation->philosophers[j].id,
				simulation->philosophers[j].times_eaten, RESET);
		}
	}
	else
		ft_printf("%sA philosopher died.%s\n", REDB, RESET);
	if (i == 1)
		ft_printf("Simulation ended after %dms.%s\n",
			(simulation->time_die), RESET);
	else
		ft_printf("Simulation ended after %dms.%s\n", get_time()
			- simulation->start_time, RESET);
	ft_printf("%s=================================\n%s", BGRN, RESET);
}

void	print_simulation_details(t_simulation *simulation)
{
	ft_printf("%sDetails of the simulation:\n%s", CYN, RESET);
	ft_printf("%s- Number of philosophers and forks: %d\n", BYEL,
		simulation->num_phi);
	ft_printf("%s- Time to die: %d ms\n", BYEL, simulation->time_die);
	ft_printf("- Time to eat: %d ms\n", simulation->time_eat);
	ft_printf("- Time to sleep: %d ms\n", simulation->time_sleep);
	if (simulation->num_must_eat > 0)
	{
		ft_printf("- Number of times each philosopher must eat: %d%s\n",
			simulation->num_must_eat, RESET);
	}
	else
	{
		ft_printf("- Number of times each philosopher must eat: ");
		ft_printf("Not specified%s\n",
			RESET);
	}
	ft_printf("%sStarting simulation...%s\n", GRN, RESET);
	ft_printf("\n");
	sleep(2);
}
