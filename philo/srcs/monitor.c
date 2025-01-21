/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:42:26 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 20:23:47 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philosopher(t_simulation *simulation, int i,
		int *all_satisfied)
{
	long	current_time;

	pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
	current_time = get_time();
	if (current_time
		- simulation->philosophers[i].last_meal_time > simulation->time_die)
	{
		log_action(&simulation->philosophers[i], "died", REDB);
		set_simul_over(simulation, 1);
	}
	pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
	if (simulation->num_must_eat > 0)
	{
		pthread_mutex_lock(&simulation->philosophers[i].times_eaten_mutex);
		if (simulation->philosophers[i].times_eaten < simulation->num_must_eat)
			*all_satisfied = 0;
		pthread_mutex_unlock(&simulation->philosophers[i].times_eaten_mutex);
	}
	return (NULL);
}

void	*monitor_simulation(void *arg)
{
	t_simulation	*simulation;
	int				i;
	int				all_satisfied;

	simulation = (t_simulation *)arg;
	while (!is_simul_over(simulation))
	{
		all_satisfied = 1;
		i = 0;
		while (i < simulation->num_phi)
		{
			monitor_philosopher(simulation, i, &all_satisfied);
			i++;
		}
		if (simulation->num_must_eat > 0 && all_satisfied)
			set_simul_over(simulation, 1);
		usleep(500);
	}
	return (NULL);
}
