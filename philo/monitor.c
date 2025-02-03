/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:42:26 by ngaurama          #+#    #+#             */
/*   Updated: 2025/02/03 15:19:42 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philosopher(t_simulation *simulation, int i,
		int *all_satisfied)
{
	long	current_time;
	long	last_meal;

	pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
	current_time = get_time();
	last_meal = simulation->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
	if (current_time - last_meal > simulation->time_die)
	{
		log_action(&simulation->philosophers[i], "died", REDB);
		pthread_mutex_lock(&simulation->simul_over_mutex);
		simulation->simul_over = 1;
		pthread_mutex_unlock(&simulation->simul_over_mutex);
	}
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
	while (!simulation->simul_over)
	{
		all_satisfied = 1;
		i = 0;
		while (i < simulation->num_phi)
		{
			monitor_philosopher(simulation, i, &all_satisfied);
			i++;
		}
		if (simulation->num_must_eat > 0 && all_satisfied)
		{
			pthread_mutex_lock(&simulation->simul_over_mutex);
			simulation->simul_over = 2;
			pthread_mutex_unlock(&simulation->simul_over_mutex);
		}
		usleep(100);
	}
	return (NULL);
}
