/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:40:53 by ngaurama          #+#    #+#             */
/*   Updated: 2025/02/01 15:02:12 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long duration_ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < duration_ms)
		usleep(100);
}

void	log_action(t_philo *philo, const char *action, char *color)
{
	long	timestamp;

	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (!is_simulation_over(philo))
	{
		timestamp = get_time() - philo->simulation->start_time;
		printf("%s%ld %d %s" RESET "\n", color, timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->simulation->print_mutex);
}

int	is_simulation_over(t_philo *philo)
{
	int	over;

	pthread_mutex_lock(&philo->simulation->simul_over_mutex);
	over = philo->simulation->simul_over;
	pthread_mutex_unlock(&philo->simulation->simul_over_mutex);
	return (over);
}

// void thinking(t_philo *philo, int value)
// {
// 	long think_time;

// 	if (!value)
// 		log_action(philo, "is thinking", WHT);
// 	if (philo->simulation->num_phi % 2 == 0)
// 		return ;
// 	think_time = (philo->simulation->time_eat * 2)
//	- philo->simulation->time_sleep;
// 	if (think_time < 0)
// 		think_time = 0;
// 	precise_sleep(5);
// }
