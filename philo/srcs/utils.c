/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:40:53 by ngaurama          #+#    #+#             */
/*   Updated: 2025/01/21 17:04:58 by ngaurama         ###   ########.fr       */
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

void	log_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (!philo->simulation->simul_over)
		printf("%ld %d %s\n", get_time() - philo->simulation->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->simulation->print_mutex);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
}
