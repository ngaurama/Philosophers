/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:55:32 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/29 00:01:42 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	print_intro();
	if (!init_input(argv, argc, &simulation))
		return (1);
	if (init_input(argv, argc, &simulation) == 2)
		return (single_philo(&simulation));
	print_simulation_details(&simulation);
	if (!init_philo(&simulation))
		return (1);
	start_threads(&simulation);
	print_summary(&simulation, 0);
	cleanup_simulation(&simulation);
	return (0);
}
